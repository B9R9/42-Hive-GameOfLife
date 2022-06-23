#include "gol_opt.h"

void print_map(char *map, int row, int iteration);

void err_mes(char *message)
{
	printf("%s\n", message);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	neg;
	int	i;
	int	result;

	result = 0;
	i = 0;
	neg = 1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
	{
		neg = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * neg);
}

void	ft_bzero(void	*s, size_t	n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n > 0)
	{
		*p++ = '\0';
		n--;
	}
}

void	*ft_memcpy(void	*dest, const void	*src, size_t n)
{
	unsigned char	*pdst;

	if (n && (!dest && !src))
		return (NULL);
	pdst = (unsigned char *)dest;
	while (n--)
		*pdst++ = *(unsigned char *)src++;
	return (dest);
}

void	*ft_memalloc(size_t	size)
{
	unsigned char	*arr;

	arr = (unsigned char *)malloc(size);
	if (arr == NULL)
		return (NULL);
	ft_bzero(arr, size);
	return (arr);
}

char	*ft_strnew(size_t size)
{
	return ((char *)ft_memalloc(size + 1));
}

size_t	ft_strlen(const char	*s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strcat(char	*s1, char const *s2)
{
	size_t	len_s1;

	len_s1 = ft_strlen(s1);
	ft_memcpy(s1 + len_s1, s2, ft_strlen(s2));
	ft_bzero(s1 + len_s1 + ft_strlen(s2), 1);
	return (s1);
}

char	*ft_strcpy(char	*dst, const char	*src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin(char const	*s1, char const	*s2)
{
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	join = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (!join)
		return (NULL);
	ft_strcpy(join, s1);
	ft_strcat(join, s2);
	return (join);
}

char	*ft_strchr(const char	*s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

int check_map(char **arr, t_data **data, int argc)
{
	char line[MAX_SIZE];
	char *position_new_line = NULL;
	int countline = 0;
	FILE *fp;

	(*data)->refmap = ft_strnew(1);
	ft_bzero((*data)->refmap, 1);

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
		(*data)->refmap = ft_strjoin((*data)->refmap, line);
	}
	fclose(fp);
	(*data)->line = countline;
	(*data)->row = ft_strlen(line);
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
	if (start % data->row == i % data->row || i % data->row == data->row - 1)
		return (1);
	return (2);
}

int check_region(int i, t_data *data)
{

	int x = 0, n = 0, move = 0, j = 1;
	int start = define_start(i, data);
	int end = define_end(i, data);
	int max_move = define_move(i, start, data);

	x = start;
	while (x <= end)
	{
		if(data->refmap[x] == 'X' && x != i)
			n++;
		if (x == end)
			break;
		if (move  == max_move)
		{
			x = ( start + (j * data->row)) - 1;
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
	int i = 0;
	printf("================ %d =============\n", iteration);
	while (map[i] != '\0')
	{
		if (i % row == 0)
		{
			printf("\n");
		}
		if(map[i] == 'X')
	    	printf("%s%c%s", "\x1B[32m", map[i], "\x1B[0m");
		else
			printf("%c", map[i]);
	    i++;
	}
	printf("\n");

}

void    solver(t_data *d, int visuel)
{
	int i = 0;
	int n = 0;
	int last_position = d->row * d->line;
	int z = 0;
	char *newmap = (char *)malloc(sizeof(char) * last_position);
	while (z < d->iteration)
	{
		i = 0;
		while (i < last_position)
		{
			n = check_region(i, d);
			if ((n == 3) || (n == 2 && d->refmap[i] == 'X'))
		    	newmap[i] = 'X';
			else
		    	newmap[i] = '.';
			i++;
			n = 0;
		}
		newmap[i] = 0;
		if (visuel)
			print_map(newmap, d->row, z);
		char *temp = d->refmap;
		d->refmap = newmap;
		newmap = temp;
		z++;
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

// int check_option(int argc, char **argv)
// {
// 	int i = 1;
// 	while (i < argc)
// 	{
// 		if(argv[i][0] == '-' && argv[i][1] == 'v')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

int main (int argc, char **argv)
{
	t_data *data;

	data = malloc(sizeof(data));

	if(check_error(argc, argv,&data))
		return (0);
	data->iteration = ft_atoi(argv[argc - 1]);
	solver(data, 0);
	print_map(data->refmap,data->row,0);
	return (0);
}
