#ifndef PAC_MAN_H
#define PAC_MAN_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# include <signal.h>

# define    WALL_CHAR   'W'


typedef struct s_list
{
	void            *content;
	struct s_list	*next;
}	            t_list;


typedef struct s_vect2d
{
    int x;
    int y;
}               t_vect2d;

typedef struct  s_ghost
{
    int         type;
    t_vect2d    *ghost;
    t_vect2d    *normal;
    char        old;
}           t_ghost;


typedef struct s_pacman
{
    char        **map;
    char        **astar_map;
    t_ghost     *pacman;
    t_ghost     *blinky;
    t_ghost     *pinky;
    t_ghost     *inky;
    t_ghost     *clyde;
    int         pac_points;
    int         playing;
    pthread_t   *ghosts_th;
	pthread_t	*pacman_th;
}               t_pacman;

typedef struct  s_astar
{
    t_vect2d    pos;
    t_vect2d    father;
    double       f_coast;
    double      h_coast;
    double      g_coast;
}               t_anode;

#endif