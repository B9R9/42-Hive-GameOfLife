#ifndef GOL_H
# define GOL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>

# define MAX_SIZE 10000

typedef struct s_data {
    int line;
    int row;
    int iteration;
    char *refmap;
    char *newmap;
}   t_data;

#endif
