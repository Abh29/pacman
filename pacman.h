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
# define	SLEEP_PACMAN	10000		//10 ms
# define	SLEEP_GHOSTS	10000
# define	SLEEP_GHOSTS_S	1
# define	SLEEP_DISPLAY	10000		// 33ms ~ 30hz
# define	CLEAR_OUTPUT	0 //  set this to 1 to clear the screan in play mode
# define	DISPLAY_MSG		1 //	set this to 1 to display game status messages (win, loose, quit...)
# define	MODE			0 // 0 for testing 1 for playing

# define	UP_CHAR		'z'		//controlles
# define	DOWN_CHAR	's'
# define	RIGHT_CHAR	'd'
# define	LEFTF_CHAR	'w'
# define	QUIT_CHAR	'q'

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

enum weekday { //for later use to dispaly the date ...
    Montag,
    Dienstag,
    Mittwoch,
    Donnerstag,
    Freitag,
    Samstag,
    Sonntag
};

typedef struct  s_ghost
{
    int         type;
    t_vect2d    *ghost;
    t_vect2d    *normal;
    char        old;
	pthread_t	*ghost_th;
	int			dispaly;
}           t_ghost;


typedef struct s_pacman
{
    char        **map;
    char        **astar_map;
	char		**original_map;
    t_ghost     *pacman;
    t_ghost     *blinky;
    t_ghost     *pinky;
    t_ghost     *inky;
    t_ghost     *clyde;
    int         pac_points;
    int         playing;
	int			last_map;
    pthread_t   *screen_th;
}               t_pacman;

typedef struct  s_astar
{
    t_vect2d    pos;
    t_vect2d    father;
    double       f_coast;
    double      h_coast;
    double      g_coast;
}               t_anode;


/*********tools**************/
void    	ft_putstr_file(char *str, FILE *file);
void    	ft_exit(char *msg, FILE *file, int err);
int			nanosleep(const struct timespec *req, struct timespec *rem);
void		ft_sleep(int sec);
void		ft_usleep(int usec);
char		*ft_strdup(char *str);
/***********vect*************/
t_vect2d	*ft_vectnew(int x, int y);
void		ft_print_vect(t_vect2d *vect);
void		ft_vect_sum(t_vect2d *res, t_vect2d *v1, t_vect2d *v2);
void		ft_vect_dif(t_vect2d *diff, t_vect2d *a, t_vect2d *b);
void		ft_vect_mult_scal(t_vect2d *res, t_vect2d *a, int scal);
int			ft_vect_eql(t_vect2d *a, t_vect2d *b);
double		ft_distance(t_vect2d *a, t_vect2d *b);

/******list******************/
t_list		*ft_lstnew(void *content);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstremove(t_list **lst, void *elm, int (*cmp)(void *, void *), void (*dell)(void *));
void		ft_lstremove_one(t_list **lst, void *elm, int (*cmp)(void *, void *), void (*dell)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void*));
t_list		*ft_lst_in(t_list *lst, void *elm, int (*cmp)(void *, void *));
char		*ft_ltoa(t_list *lst);

/**********get next line ***********/
char		*get_next_line_nl(FILE *file);

/***********get level *******************/
t_ghost		*ft_newghost(int type);
void		ft_init_level(t_pacman *pac);
void		ft_get_map(t_pacman *pacman, FILE *input);
void		ft_get_astar_map(t_pacman *pac);
void		ft_dup_original_map(t_pacman *pac);
void		ft_put_ghosts(t_pacman *pac);
void		ft_remove_ghosts(t_pacman *pac);
void		ft_print_map(t_pacman *pac);
void		ft_get_enteties(t_pacman *pac);
void		ft_end_game(t_pacman *pac, int succ);
void		ft_free_ghost(t_ghost **ghost);
void		ft_free_pac(t_pacman *pac);

/*********************Astar***************/
t_anode		*ft_new_node(t_vect2d *pos, t_anode *father, t_vect2d *dest);
t_anode		*ft_node_dup(t_anode *node);
int			ft_anode_pos_eql(void *n1, void *n2);
int			ft_anode_cmp(void *n1, void *n2);
t_anode		*ft_min_node(t_list	*nodes);
void		ft_free_anode(void *node);
int			ft_last_step(t_anode *current, t_vect2d *end);
void		ft_get_neighbors(char **map, t_anode *neighbor[4], t_anode *current, t_vect2d *end);
t_list		*ft_get_path(t_anode *last, t_list *closed);
t_list		*ft_astar(char	**map, t_vect2d *start, t_vect2d *goal);

/*********************move*********************/
int			ft_can_move(t_pacman *pac, t_vect2d *current, t_vect2d *step);
void		ft_move_pacman(t_pacman *pac);
void		ft_get_normal(t_vect2d *normal, t_vect2d *src, t_vect2d *dest);
void		ft_get_second_normal(t_vect2d *normal, t_vect2d *src, t_vect2d *dest);
void		ft_get_random_normal(t_vect2d *normal);
void		ft_move_blinky_dumb(t_pacman *pac);
void		ft_move_pinky_dumb(t_pacman *pac);
void		ft_get_blinkys_target(t_pacman *pac, t_vect2d *target);
void		ft_get_pinkys_target(t_pacman *pac, t_vect2d *target);
void		ft_get_inkys_target(t_pacman *pac, t_vect2d *target);
void		ft_get_clydes_target(t_pacman *pac, t_vect2d *target);
void		ft_next_step(t_pacman *pac, t_ghost *ghost, void (*get_target)(t_pacman *, t_vect2d *));
void		ft_move_clyde_dumb(t_pacman *pac);
void		ft_move_inky_dumb(t_pacman *pac);

/****************** threads  ****************/
void		ft_move_ghost(t_pacman *pac, t_ghost *ghost);
void		*ft_move_blinky(void *args);
void		*ft_move_pinky(void *args);
void		*ft_move_inky(void *args);
void		*ft_move_clyde(void *args);
void		*ft_display_thread(void *args);
void		*pacman_thread(void *args);
void		ft_cancel_threads(t_pacman *pac);

/*******************level********************/
void		ft_level(FILE *infile);

#endif