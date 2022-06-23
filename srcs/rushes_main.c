#include "gol.h"

void err_mes(char *message)
{
	printf("%s\n", message);
}

void create_map( char *line, t_data **data)
{
	(*data)->refmap = ft_strjoin((*data)->refmap, line);
}


int check_map(char **arr, t_data **data, int argc)
{
	char line[MAX_SIZE];
	char *position_new_line = NULL;
	int i = 0;
	int countline = 0;
	FILE *fp;

	(*data)->refmap = ft_strnew(1);
	fp = fopen (arr[argc - 2], "r");
	if (fp == NULL)
	{
		err_mes("Empty file or wrong file");
		return (1);
	}
	while(fgets(line, MAX_SIZE, fp) != NULL)
	{
		countline++;
		position_new_line = ft_strchr(line,'\n');
		if(position_new_line !=  NULL)
			*position_new_line = '\0';
		i = 0;
		while (line[i] != '\0')
		{
			if (line[i] == '.' || line[i] == 'X')
				i++;
			else
				return (1);
		}
		(*data)->row  = i;
		create_map(line, data);
	}
	fclose(fp);
	(*data)->line = countline;
	(*data)->row = i;
	return (0);
}


int define_start(int i , t_data *data)
{
	int row = data->row;
	if (i / row == 0)
	{
		if (i % row  == 0)
			return (i);
		else
			return (i - 1);
	}
	else
	{
		if(i % row == 0)
			return (i - row);
		else
			return((i - row) - 1);
	}
	return (-1);
}

int define_end(int i, t_data *data)
{
	int row = data->row, line = data->line;
	if (i  == (row * line - 1))
		return (i);
	if ( i % row == row - 1)
		return ( i + row);
	if (i / row == line - 1)
		return ( i + 1);
	else
		return( i + row + 1);
	return (-1);

}

int define_move(int i, int start, t_data *data)
{
	if (start % data->row == i % data->row)
		return (1);
	else if (i % data->row == data->row - 1)
		return (1);
	else
		return (2);
	return (-1);

}

int check_region(int i, t_data **data)
{

	int x = 0, n = 0, move = 0, j = 1;
	int start = define_start(i, *data);
	int end = define_end(i, *data);
	int max_move = define_move(i, start, *data);

	x = start;
	while (x <= end)
	{
		if((*data)->refmap[x] == 'X' && x != i)
			n++;
		if (x == end)
			break;
		if (move  == max_move)
		{
			x = ( start + (j *(*data)->row)) - 1;
			j += 1;
			move = -1;
		}
		x++;
		move++;
	}
	return (n);
}

void print_map(char *map, int row, int iteration)
{
	sleep(1);
	system("clear");
	int x = 0, i = 0;
	printf("================ %d =============\n", iteration);
	while (map[i] != '\0')
		{
			if(map[i] == 'X')
	    		printf("%s%c%s", "\x1B[32m", map[i], "\x1B[0m");
			else
				printf("%c", map[i]);
			if(x == row - 1)
	    	{
				printf("\n");
	        	x = -1;
	    	}
	    	x++;
	    	i++;
		}
}

void    solver(t_data **d, int visuel)
{
	int i = 0;
	int n = 0;

	while ((*d)->iteration >= 0)
	{
		(*d)->newmap = ft_strnew((*d)->row * (*d)->line);
		i = 0;
		while (i < (*d)->line * (*d)->row)
		{
			n = check_region(i, d);
			if ((n == 3) | (n == 2 && (*d)->refmap[i] == 'X'))
		    	(*d)->newmap[i] = 'X';
			else
		    	(*d)->newmap[i] = '.';
			i++;
			n = 0;
		}
		(*d)->newmap[i] = 0;
		if (visuel)
			print_map((*d)->newmap, (*d)->row, ((*d)->iteration));
		(*d)->refmap = ft_strdup((*d)->newmap);
		ft_strdel(&(*d)->newmap);
		(*d)->iteration--;
	}
}

int check_error(int size, char **tab, t_data **data)
{
	int i = 0;
	if (size < 3)
{        err_mes("./life  <options> <initialestate> <iteration>");
		return (1);}
	while (tab[i][0] == '-')
	{
		if(!ft_isalpha(tab[0][1]))
		{
			err_mes("Wrong option");
			return (1);
		}
		i++;
	}
	if (ft_atoi(tab[size - 1]) == 0)
{        err_mes("Iteration need to be a digit or bigger then 0");
		return (1);}
	if (check_map(tab, data, size))
{        err_mes("Wrong initialestate");
		return (1);}
	return (0);
}

int check_option(int argc, char **argv)
{
	int i = 1;
	while (i < argc)
	{
		if(argv[i][0] == '-' && argv[i][1] == 'v')
			return (1);
		i++;
	}
	return (0);
}

int main (int argc, char **argv)
{
	t_data *data;

	data = malloc(sizeof(data));

	if(check_error(argc, argv,&data))
		return (0);
	data->iteration = ft_atoi(argv[argc - 1]);
	solver(&data, check_option(argc,argv));
	print_map(data->refmap,data->row, data->iteration);
	return (0);
}
