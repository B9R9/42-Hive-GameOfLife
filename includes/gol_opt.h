#ifndef GOL_OPT_H
# define GOL_OPT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define MAX_SIZE 10000

typedef struct s_data {
    int line;
    int row;
    int iteration;
    char *refmap;
}   t_data;

#endif
