#include "gol.h"

void err_mes(char *message)
{
	printf("%s\n", message);
}

void create_map( char *line, t_data **data)
{
	(*data)->refmap = ft_strjoin((*data)->refmap, line);
}


int check_map(char **arr, t_data **data)
{
	char line[MAX_SIZE];
	char *position_new_line = NULL;
	int i = 0;
	int countline = 0;
	FILE *fp;

	(*data)->refmap = ft_strnew(1);
	fp = fopen (arr[1], "r");
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


// int check_around(int i, t_data **d)
// {
//     int n = 0;
//     while (i < (*d)->row * (*d)->line)
//     {
//         // check up
//         if (i - (*d)->line >= 0)
//         {
//             if ((*d)->refmap[i - (*d)->line] == 'X')
//                 n++;
//         }
//         // check up-left
//         if (i - (*d)->line >= 0 && (i - 1) % (*d)->line != (*d)->line - 1)
//         {
//             if ((*d)->refmap[i - (*d)->line - 1] == 'X')
//                 n++;
//         }
//         //check up-right
//         if (i - (*d)->line >= 0 && (i + 1) % (*d)->line != 0)
//         {
//             if ((*d)->refmap[i - (*d)->line + 1] == 'X')
//                 n++;
//         }
//         // check down
//         if (i + (*d)->line < (*d)->row * (*d)->line)
//         {
//             if ((*d)->refmap[i + (*d)->line] == 'X')
//                 n++;
//         }
//         // check down-left
//         if (i + (*d)->line < (*d)->row * (*d)->line && (i - 1) % (*d)->line != (*d)->line - 1)
//         {
//             if ((*d)->refmap[i + (*d)->line - 1])
//                 n++;
//         }
//         // check down-right
//         if (i + (*d)->line < (*d)->row * (*d)->line && (i + 1) % (*d)->line != 0)
//         {
//             if ((*d)->refmap[i + (*d)->line + 1])
//                 n++;
//         }
//         // check left
//         if ((i - 1) % (*d)->line != (*d)->line - 1)
//         {
//             if ((*d)->refmap[i - 1] == 'X')
//                 n++;
//         }
//         // check right
//         if ((i + 1) % (*d)->line != 0)
//         {
//             if ((*d)->refmap[i + 1] == 'X')
//                 n++;
//         }
//         if ((n == 3) | (n == 2 && (*d)->refmap[i] == 'X'))
//             (*d)->newmap[i] = 'X';
//         else
//             (*d)->newmap[i] = '.';
//         i++;
//         n = 0;
//     }
// }


// int check_left(int position, t_data *data)
// {
//     if(((position - 1) / data->row) == (position / data->row) &&
//     ((position - 1) >= 0))
//         if (data->refmap[i - 1] == 'X')
//             return (1);
//     return (0);
// }

// int check_right(int i, t_data *data)
// {
//     if (i + 1 / data->row == i / data->row && i + 1 < data->row)
//         if (data->refmap[i + 1] == 'X')
//             return (1);
//     return (0);
// }

// int check_up(i, t_data *data)
// {
//     int to_check = i + data->row;
//     while ((to_check / data->row == i / data->row + 1) &&
//     to_check / row < data->line && )
//     {
//         if (check_left(to_check))
//     }
//     return (0);
// }

// int checkregion(char k, char grid[9][9], int i, int j)
// {
//     int n;
// 	int _i = i-(i%3);
// 	int _j = j-(j%3);
// 	i = _i;
// 	j = _j;
// 	while (i<_i+3)
// 	{
// 		while(j < _j +3)
// 		{
// 			if (grid[i][j] == 'X')
// 				n++;
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (n);
// }
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


void    solver(t_data **d)
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
		i = 0;
		system("clear");
		int x = 0;
		printf("************   %d   **************\n",(*d)->iteration);
		while ((*d)->newmap[i] != '\0')
		{
	    	printf("%c", (*d)->newmap[i]);
	    	if(x == (*d)->row - 1)
	    	{
				printf("\n");
	        	x = -1;
	    	}
	    	x++;
	    	i++;
		}
		sleep(1);
		system("clear");
		(*d)->refmap = ft_strdup((*d)->newmap);
		ft_strdel(&(*d)->newmap);
		(*d)->iteration--;
	}
}

int check_error(int size, char **tab, t_data **data)
{
	if (size != 3)
{        err_mes("./life <initialestate> <iteration>");
		return (1);}
	if (ft_atoi(tab[2]) == 0)
{        err_mes("Iteration need to be a digit or bigger then 0");
		return (1);}
	if (check_map(tab, data))
{        err_mes("Wrong initialestate");
		return (1);}
	return (0);
}

int main (int argc, char **argv)
{
	t_data *data;

	data = malloc(sizeof(data));

	if(check_error(argc, argv,&data))
		return (0);
	data->iteration = ft_atoi(argv[2]);
	solver(&data);
	return (0);
}
