#include "pacman.h"

/*********tools**************/
void    ft_putstr_file(char *str, FILE *file)
{
    fwrite(str, strlen(str), 1, file);
}

void    ft_exit(char *msg, FILE *file, int err)
{
    ft_putstr_file(msg, file);
    exit(err);
}

void	ft_sleep(int sec)
{
	struct timespec remaining, request;

	if (sec <= 0)
		return ;
	request.tv_sec = sec;
	request.tv_nsec = 0;
    nanosleep(&request, &remaining);
}

void	ft_usleep(int usec)
{
	struct timespec remaining, request;

	if (usec <= 0)
		return ;
	request.tv_sec = usec / 1000000;
	request.tv_nsec = usec % 1000000;
    nanosleep(&request, &remaining);
}

char	*ft_strdup(char *str)
{
	size_t 	i;
	char	*out;

	if (str == NULL)
		return (NULL);
	out = malloc (strlen(str) + 1);
	if (out == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		out[i] = str[i];
		i++;
	}
	out[i] = 0;
	return (out);
}

/***********end tools *******/
/***********vect*************/
t_vect2d	*ft_vectnew(int x, int y)
{
	t_vect2d *out;

	out = malloc(sizeof(t_vect2d));
	if (out == NULL)
		return (NULL);
	out->x = x;
	out->y = y;
	return (out);
}

void		ft_print_vect(t_vect2d *vect)
{
	if (vect == NULL)
		printf("(null)\n");
	else
		printf("(%3d, %3d)\n", vect->x, vect->y);
}

void		ft_vect_sum(t_vect2d *res, t_vect2d *v1, t_vect2d *v2)
{

	if (res == NULL || v1 == NULL || v2 == NULL)
		return ;
	res->x = v1->x + v2->x;
	res->y = v1->y + v2->y;
}

void		ft_vect_dif(t_vect2d *diff, t_vect2d *a, t_vect2d *b)
{
	if (!diff || !a || !b)
		return ;
	diff->x = b->x - a->x;
	diff->y = b->y - a->y;
}

void		ft_vect_mult_scal(t_vect2d *res, t_vect2d *a, int scal)
{
	if (!res || !a)
		return ;
	res->x *= scal;
	res->y *= scal;
}

int			ft_vect_eql(t_vect2d *a, t_vect2d *b)
{
	return (a->x == b->x && a->y == b->y);
}

double		ft_distance(t_vect2d *a, t_vect2d *b)
{
	if (!a || !b)
		return (-1);
	return (sqrt(pow(b->x - a->x, 2) + pow(b->y - a->y, 2)));
}
/**********end vect**********/
/******list******************/
t_list	*ft_lstnew(void *content)
{
	t_list	*out;

	out = malloc(sizeof(t_list));
	if (out == NULL)
		return NULL;
	out->content = content;
	out->next = NULL;
	return (out);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*save;

	if(*lst == NULL)
	{
		*lst = new;
		return;	
	}
	save = *lst;
	while(save->next)
		save = save->next;
	save->next = new;
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}

int		ft_lstsize(t_list *lst)
{
	int		length;

	length = 0;
	while (lst)
	{
		lst = lst->next;
		length++;
	}
	return (length);
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*p;

	if (*lst == NULL)
		return;
	while (*lst)
	{
		p = *lst;
		*lst = (*lst)->next;
		if (del)
			del(p->content);
		free(p);
	}
	free(*lst);
}

void	ft_lstremove(t_list **lst, void *elm, int (*cmp)(void *, void *), void (*dell)(void *))
{
	t_list	*current;
	t_list	*p;
	t_list	*past;

	if (lst == NULL || *lst == NULL)
		return ;
	current = *lst;
	past = NULL;
	p = NULL;
	while (current)
	{
		if (cmp(current->content, elm) == 0)
		{
			if (past)
				past->next = current->next;
			else
				*lst = current->next;
			p = current;
			current = current->next;
			if (dell)
				dell(p->content);
			free(p);
			p = NULL;
		}
		else
		{
			past = current;
			current = current->next;
		}
	}
}

void	ft_lstremove_one(t_list **lst, void *elm, int (*cmp)(void *, void *), void (*dell)(void *))
{
	t_list	*current;
	t_list	*p;
	t_list	*past;

	if (lst == NULL || *lst == NULL)
		return ;
	current = *lst;
	past = NULL;
	p = NULL;
	while (current)
	{
		if (cmp(current->content, elm) == 0)
		{
			if (past)
				past->next = current->next;
			else
				*lst = current->next;
			p = current;
			current = current->next;
			if (dell)
				dell(p->content);
			free(p);
			p = NULL;
			return ;
		}
		else
		{
			past = current;
			current = current->next;
		}
	}
}

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == NULL)
		return ;
	del(lst->content);
	free(lst);
}

t_list	*ft_lst_in(t_list *lst, void *elm, int (*cmp)(void *, void *))
{
	if (!lst || !cmp)
		return (NULL);
	while (lst)
	{
		if (cmp(lst->content, elm) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

char	*ft_ltoa(t_list *lst)
{
	int		size;
	char	*out;
	char	*save;

	if (lst == NULL)
		return (NULL);
	size = ft_lstsize(lst);
	if (size <= 0)
		return (NULL);
	out = malloc(size + 1);
	if (out == NULL)
		return (NULL);
	save = out;
	while (lst)
	{
		*save = *((char *)lst->content);
		save++;
		lst = lst->next;
	}
	*save = 0;
	return (out);
}

/**********end list ******************/
/**********get next line ***********/
char	*get_next_line_nl(FILE *file)
{
	char			*c;
	char			*out;
	t_list			*tmp;
	int				r;

	if (file == NULL)
		return (NULL);
	tmp = NULL;
	c = malloc(1);
	*c = 0;
	r = 0;
	while (fscanf(file, "%c", c) == 1)
	{
		r = 1;
		ft_lstadd_back(&tmp, ft_lstnew(c));
		if (*c == '\n')
			break ;
		c = malloc(1);
	}
	if (r == 0)
		free(c);
	if (r && *c != '\n')
	{
		*c = '\n';
		ft_lstadd_back(&tmp, ft_lstnew(c));
	}
	out = ft_ltoa(tmp);	
	ft_lstclear(&tmp, free);
	return (out);
}

/***********end get next line **********/
/***********get level *******************/
t_ghost	*ft_newghost(enum entity type)
{
	t_ghost	*out;

	out = malloc(sizeof(t_ghost));
	if (out == NULL)
		return (NULL);
	out->type = type;
	out->ghost = NULL;
	out->dispaly = 1;
	out->normal = ft_vectnew(0, 0);
	out->ghost_th = malloc(sizeof(pthread_t));
	out->old = 0;
	return (out);
}

void	ft_init_level(t_pacman *pac)
{
	if (pac == NULL)
		return ;
	pac->pac_points = 0;
	pac->playing = 1;
	pac->screen_th = NULL;
	pac->map = NULL;
	pac->original_map = NULL;
	pac->last_map = 0;
	pac->quit = 0;
	pac->screen_th = malloc(sizeof(pthread_t));
	pac->pacman = ft_newghost(Pacman);
	pac->blinky = ft_newghost(Blinky);
	pac->pinky = ft_newghost(Pinky);
	pac->inky = ft_newghost(Inky);
	pac->clyde = ft_newghost(Clyde);
}

void	ft_get_map(t_pacman *pacman, FILE *input)
{
	t_list	*tmp;
	t_list	*p;
	char	*line;
	char	**save;
	size_t	size;

	if (pacman == NULL || input == NULL)
		return ;
	line = get_next_line_nl(input);
	if (line == NULL)
	{
		if (ferror(input) != 0)
			ft_exit("Error : input file internal error !\n", stderr, 40);
		ft_exit("Error : empty input file !\n", stderr, 41);
	}
		
	tmp = NULL;
	while (line)
	{
		ft_lstadd_back(&tmp, ft_lstnew(line));
		line = get_next_line_nl(input);
	}
	size = ft_lstsize(tmp) + 1;
	pacman->map = malloc(size * sizeof(char *));
	pacman->astar_map = malloc(size * sizeof(char *));
	pacman->original_map = malloc(size * sizeof(char *));
	if (!pacman->map || !pacman->original_map || !pacman->astar_map)
		ft_exit("Error : could not allocate memory for maps!\n", stderr, 1);
	save = pacman->map;
	p = tmp;
	while (tmp)
	{
		*save = (char *)tmp->content;
		save++;
		tmp = tmp->next;
	}
	*save = NULL;
	ft_lstclear(&p, NULL);
}

void	ft_get_astar_map(t_pacman *pac)
{
	int		i;
	int		j;

	if (pac->map == NULL || pac->astar_map == NULL)
		return ;
	i = 0;
	while (pac->map[i])
	{
		pac->astar_map[i] = malloc(strlen(pac->map[i]) + 1);
		if (pac->astar_map[i] == NULL)
			ft_exit("Error : could not allocate memory for astrix_map !\n", stderr, 1);
		j = 0;
		while (pac->map[i][j])
		{
			pac->astar_map[i][j] = pac->map[i][j] == WALL_CHAR ? '0' : '1';
			j++;
		}
		pac->astar_map[i][j] = 0;
		i++;
	}
	pac->astar_map[i] = NULL;
}

void	ft_dup_original_map(t_pacman *pac)
{
	int	i;

	if (pac == NULL)
		return ;
	i = 0;
	while (pac->map[i])
	{
		pac->original_map[i] = ft_strdup(pac->map[i]);
		i++;
	}
	pac->original_map[i] = NULL;
	if (pac->pacman->ghost)
		pac->original_map[pac->pacman->ghost->x][pac->pacman->ghost->y] = ' ';
	if (pac->blinky->ghost)
		pac->original_map[pac->blinky->ghost->x][pac->blinky->ghost->y] = ' ';
	if (pac->pinky->ghost)
		pac->original_map[pac->pinky->ghost->x][pac->pinky->ghost->y] = ' ';
	if (pac->inky->ghost)
		pac->original_map[pac->inky->ghost->x][pac->inky->ghost->y] = ' ';
	if (pac->clyde->ghost)
		pac->original_map[pac->clyde->ghost->x][pac->clyde->ghost->y] = ' ';
}

void	ft_put_ghosts(t_pacman *pac)
{
	if (!pac)
		return ;
	if (pac->pacman->ghost && pac->pacman->dispaly)
	{
		pac->pacman->old = pac->original_map[pac->pacman->ghost->x][pac->pacman->ghost->y];
		pac->map[pac->pacman->ghost->x][pac->pacman->ghost->y] = 'P';
	}
	if (pac->blinky->ghost && pac->blinky->dispaly)
	{
		pac->blinky->old = pac->original_map[pac->blinky->ghost->x][pac->blinky->ghost->y];
		pac->map[pac->blinky->ghost->x][pac->blinky->ghost->y] = 'B';
	}
	if (pac->pinky->ghost && pac->pinky->dispaly)
	{
		pac->pinky->old = pac->original_map[pac->pinky->ghost->x][pac->pinky->ghost->y];
		pac->map[pac->pinky->ghost->x][pac->pinky->ghost->y] = 'Y';
	}
	if (pac->inky->ghost && pac->inky->dispaly)
	{
		pac->inky->old = pac->original_map[pac->inky->ghost->x][pac->inky->ghost->y];
		pac->map[pac->inky->ghost->x][pac->inky->ghost->y] = 'I';
	}
	if (pac->clyde->ghost && pac->clyde->dispaly)
	{
		pac->clyde->old = pac->original_map[pac->clyde->ghost->x][pac->clyde->ghost->y];
		pac->map[pac->clyde->ghost->x][pac->clyde->ghost->y] = 'C';
	}
}

void	ft_remove_ghosts(t_pacman *pac)
{
		if (!pac)
		return ;
	if (pac->pacman->ghost)
	{
		pac->map[pac->pacman->ghost->x][pac->pacman->ghost->y] = pac->pacman->old;
	}
	if (pac->blinky->ghost)
	{
		pac->map[pac->blinky->ghost->x][pac->blinky->ghost->y] = pac->blinky->old;
	}
	if (pac->pinky->ghost)
	{
		pac->map[pac->pinky->ghost->x][pac->pinky->ghost->y] = pac->pinky->old;
	}
	if (pac->inky->ghost)
	{
		pac->map[pac->inky->ghost->x][pac->inky->ghost->y] = pac->inky->old;
	}
	if (pac->clyde->ghost)
	{
		pac->map[pac->clyde->ghost->x][pac->clyde->ghost->y] = pac->clyde->old;
	}
}

void	ft_print_map(t_pacman *pac)
{
	char	**map;
	int		i;
	int		j;

	if (MODE && CLEAR_OUTPUT)
		if (system("clear") != 0)
			ft_exit("Error : could not execute system cmd \n", stderr, 1);
	
	map = pac->map;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			map[i][j] = pac->original_map[i][j];
			j++;
		}
		map[i][j] = 0;
		i++;
	}
	map[i] = NULL;
	ft_put_ghosts(pac);
	if (pac->last_map == 0)
		while (*map)
			printf("%s", *map++);
	fflush(stdout);
//	printf("pacman : ");
//	ft_print_vect(pac->pacman->ghost);
//	printf("Blinky : ");
//	ft_print_vect(pac->blinky->ghost);
//	printf("Pinky : ");
//	ft_print_vect(pac->pinky->ghost);
//	printf("Inky : ");
//	ft_print_vect(pac->inky->ghost);
//	printf("Clyde : ");
//	ft_print_vect(pac->clyde->ghost);	
	if (pac->playing == 0)
		pac->last_map = 1;
}

void	ft_get_enteties(t_pacman *pac)
{
	char	**tmp;
	int		i;
	int 	j;

	i = 0;
	if (pac == NULL)
		return ;
	tmp = pac->map;
	while (tmp[i])
	{
		j = 0;
		while (tmp[i][j])
		{
			if (tmp[i][j] == 'P')
			{
				if (pac->pacman->ghost)
					ft_exit("Error : there should be only one pacman !\n", stderr, 41);
				pac->pacman->ghost = ft_vectnew(i, j);
				tmp[i][j] = ' ';
			}
			else if (tmp[i][j] == 'B' && pac->blinky->ghost == NULL)
			{
				pac->blinky->ghost = ft_vectnew(i, j);
				tmp[i][j] = ' ';
			}
			else if (tmp[i][j] == 'Y' && pac->pinky->ghost == NULL)
			{
				pac->pinky->ghost = ft_vectnew(i, j);
				tmp[i][j] = ' ';
			}
			else if (tmp[i][j] == 'I' && pac->inky->ghost == NULL)
			{
				pac->inky->ghost = ft_vectnew(i, j);
				tmp[i][j] = ' ';
			}
			else if (tmp[i][j] == 'C' && pac->clyde->ghost == NULL)
			{
				pac->clyde->ghost = ft_vectnew(i, j);
				tmp[i][j] = ' ';
			}
			else if (tmp[i][j] == '.')
				pac->pac_points++;
			j++;
		}
		i++;
	}
	if (!pac->pacman->ghost)
		ft_exit("Error : no pacman is in the input file !\n", stderr, 41);
}

void	ft_end_game(t_pacman *pac, int succ)
{
	pac->playing = 0;
	ft_usleep(1000);
	if (DISPLAY_MSG)
	{
		if (succ == 1)
			printf("\nYou have won !\n");
		else if (succ == 2)
			printf("\nYou have quited the game !\n");
		else if (succ == 0)
			printf("\nyou have been eaten !\n");	
	}
	if (succ == 0)
		pac->pacman->dispaly = 0;
	ft_print_map(pac);
	if (SINGLE_THREAD == 0)
		ft_cancel_threads(pac);
}

void	ft_free_ghost(t_ghost **ghost)
{
	if (!ghost || !*ghost)
		return ;
	if ((*ghost)->ghost)
		free((*ghost)->ghost);
	free((*ghost)->ghost_th);
	free((*ghost)->normal);
	free(*ghost);
}

void	ft_free_pac(t_pacman *pac)
{
	int	i = 0;

	ft_free_ghost(&pac->pacman);
	ft_free_ghost(&pac->blinky);
	ft_free_ghost(&pac->inky);
	ft_free_ghost(&pac->clyde);
	ft_free_ghost(&pac->pinky);
	free(pac->screen_th);
	while (pac->map[i])
		free(pac->map[i++]);
	i = 0;
	while (pac->astar_map[i])
		free(pac->astar_map[i++]);
	i = 0;
	while (pac->original_map[i])
		free(pac->original_map[i++]);
	free(pac->map);
	free(pac->astar_map);
	free(pac->original_map);
}

/*********************end get level *****/
/*********************Astar***************/
t_anode	*ft_new_node(t_vect2d *pos, t_anode *father, t_vect2d *dest)
{
	t_anode	*out;

	if (!pos || !dest)
		return (NULL);
	out = malloc(sizeof(t_anode));
	if (out == NULL)
		return (NULL);
	out->pos.x = pos->x;
	out->pos.y = pos->y;
	if (father)
	{
		out->father.x = father->pos.x;
		out->father.y = father->pos.y;
		out->g_coast = father->g_coast + 1;
		out->h_coast = ft_distance(pos, dest);
	}
	else
	{
		out->father.x = -1;
		out->father.y = -1;
		out->g_coast = 0;
		out->h_coast = 0;
	}
	out->f_coast = out->g_coast + out->h_coast;
	return (out);
}

t_anode	*ft_node_dup(t_anode *node)
{
	t_anode	*out;

	if (node == NULL)
		return (NULL);
	out = malloc(sizeof(t_anode));
	if (out == NULL)
		return (NULL);
	out->pos.x = node->pos.x;
	out->pos.y = node->pos.y;
	out->father.x = node->father.x;
	out->father.y = node->father.y;
	out->f_coast = node->f_coast;
	out->g_coast = node->g_coast;
	out->h_coast = node->h_coast;
	return (out);
}

int		ft_anode_pos_eql(void *n1, void *n2)
{
	t_anode	*a;
	t_anode	*b;

	if (!n1 || !n2)
		return (0);
	if (n1 == n2)
		return (0);
	a = (t_anode *)n1;
	b = (t_anode *)n2;
	return (!ft_vect_eql(&(a->pos), &(b->pos)));
}

int		ft_anode_cmp(void *n1, void *n2)
{
	t_anode	*a;
	t_anode	*b;

	if (!n1 || !n2)
		return (0);
	if (n1 == n2)
		return (0);
	a = (t_anode *)n1;
	b = (t_anode *)n2;
	if (a->f_coast == b->f_coast)
		return ((int)(a->h_coast - b->h_coast));
	return ((int)(a->f_coast - b->f_coast));
}

t_anode	*ft_min_node(t_list	*nodes)
{
	t_anode	*out;
	t_anode	*current;

	if (nodes == NULL)
		return (NULL);
	out = nodes->content;
	nodes = nodes->next;
	while (nodes)
	{
		current = nodes->content;
		if (ft_anode_cmp(out, current) > 0)
			out = current;
		nodes = nodes->next;
	}
	return (out);
}

void	ft_free_anode(void *node)
{
	free(node);
}

int		ft_last_step(t_anode *current, t_vect2d *end)
{
	t_vect2d tmp;

	if (current == NULL)
		return (-1);
	tmp.x = current->pos.x + 1;
	tmp.y = current->pos.y;
	if (ft_vect_eql(end, &tmp))
		return (1);
	tmp.x = current->pos.x - 1;
	tmp.y = current->pos.y;
	if (ft_vect_eql(end, &tmp))
		return (1);
	tmp.x = current->pos.x;
	tmp.y = current->pos.y + 1;
	if (ft_vect_eql(end, &tmp))
		return (1);
	tmp.x = current->pos.x;
	tmp.y = current->pos.y - 1;
	if (ft_vect_eql(end, &tmp))
		return (1);
	return (0);	
}

void	ft_get_neighbors(char **map, t_anode *neighbor[4], t_anode *current, t_vect2d *end)
{
	t_vect2d tmp;

	if (current == NULL)
		return ;
	tmp.x = current->pos.x + 1;
	tmp.y = current->pos.y;
	if (map[tmp.x][tmp.y] == '1')
		neighbor[0] = ft_new_node(&tmp, current, end);
	else
		neighbor[0] = NULL;
	tmp.x = current->pos.x - 1;
	tmp.y = current->pos.y;
	if (map[tmp.x][tmp.y] == '1')
		neighbor[1] = ft_new_node(&tmp, current, end);
	else
		neighbor[1] = NULL;
	tmp.x = current->pos.x;
	tmp.y = current->pos.y + 1;
	if (map[tmp.x][tmp.y] == '1')
		neighbor[2] = ft_new_node(&tmp, current, end);
	else
		neighbor[2] = NULL;
	tmp.x = current->pos.x;
	tmp.y = current->pos.y - 1;
	if (map[tmp.x][tmp.y] == '1')
		neighbor[3] = ft_new_node(&tmp, current, end);
	else
		neighbor[3] = NULL;
}

t_list	*ft_get_path(t_anode *last, t_list *closed)
{
	t_list	*out;
	t_anode *current;
	t_anode	father;
	t_list	*tmp;

	current = last;
	out = NULL;
	while (current)
	{
		ft_lstadd_front(&out, ft_lstnew(ft_node_dup(current)));
		father.pos.x = current->father.x;
		father.pos.y = current->father.y;
		tmp = ft_lst_in(closed, &father, ft_anode_pos_eql);
		if (tmp)
			current = (t_anode *)tmp->content;
		else
			current = NULL;
	}
	return (out);
}

t_list	*ft_astar(char	**map, t_vect2d *start, t_vect2d *goal)
{
	t_list	*out;
	t_list	*open;
	t_list	*closed;
	t_list	*tmp;
	t_anode	*current;
	t_anode	*neighbor[4];
	t_anode	*tmp_anode;
	short	i;

	if (!start || !goal)
		return (NULL);
	out = NULL;
	open = NULL;
	closed = NULL;
	tmp = NULL;
	ft_lstadd_back(&open, ft_lstnew(ft_new_node(start, NULL, goal)));
	while (open)
	{
		current = ft_min_node(open);
		ft_lstremove_one(&open, current, ft_anode_pos_eql, NULL); // can optimize here !
		ft_get_neighbors(map, neighbor, current, goal);
		i = 0;
		while (i < 4)	//for each neighbor
		{
			if (neighbor[i])
			{
				if (ft_vect_eql(&(neighbor[i]->pos), goal))
				{
					ft_lstadd_front(&closed, ft_lstnew(current));
					out = ft_get_path(neighbor[i], closed);
					while (i < 4)
						ft_free_anode(neighbor[i++]);
					ft_lstclear(&open, free);
					ft_lstclear(&closed, free);
					return (out);
				}
				if (ft_lst_in(closed, neighbor[i], ft_anode_pos_eql))
				{
					ft_free_anode(neighbor[i++]);
					continue ;
				}
				tmp = ft_lst_in(open, neighbor[i], ft_anode_pos_eql);
				if (tmp)
				{
					tmp_anode = (t_anode *)tmp->content;
					if (neighbor[i]->f_coast < tmp_anode->f_coast)
					{
						tmp_anode->g_coast = neighbor[i]->g_coast;
						tmp_anode->f_coast = neighbor[i]->f_coast;
						tmp_anode->father = neighbor[i]->father;
					}
				}
				else
					ft_lstadd_back(&open, ft_lstnew(ft_node_dup(neighbor[i])));
				ft_free_anode(neighbor[i]);
			}
			i++;
		}
		ft_lstadd_back(&closed, ft_lstnew(current));
	}
	ft_lstclear(&open, free);
	ft_lstclear(&closed, free);
	return (out);
}

/*******************end Astar*************/
/*********************move*********************/
int		ft_can_move(t_pacman *pac, t_vect2d *current, t_vect2d *step)
{
		if (current == NULL || step == NULL)
			return (0);
		if (pac->map[current->x + step->x][current->y + step->y] == WALL_CHAR)
			return (0);
		return (1);
}

void	ft_move_pacman(t_pacman *pac, char c)
{
	t_vect2d 	normal;

	if (!pac || pac->playing == 0)
		return ;

	if (c == UP_CHAR)
	{			
		normal.y = 0;
		normal.x = -1;
	}
	else if (c == DOWN_CHAR)
	{
		normal.y = 0;
		normal.x = 1;
	}
	else if (c == LEFTF_CHAR)
	{
		normal.y = -1;
		normal.x = 0;
	}
	else if (c == RIGHT_CHAR)
	{
		normal.y = 1;
		normal.x = 0;
	}
	else if (c == QUIT_CHAR)
		ft_end_game(pac, 2);
	else
		return ;
	if (pac->playing && ft_can_move(pac, pac->pacman->ghost, &normal))
	{
		if (pac->pacman->old)
			pac->map[pac->pacman->ghost->x][pac->pacman->ghost->y] = pac->pacman->old;
		else
			pac->map[pac->pacman->ghost->x][pac->pacman->ghost->y] = ' ';
		pac->pacman->ghost->x += normal.x;
		pac->pacman->ghost->y += normal.y;
		if (pac->original_map[pac->pacman->ghost->x][pac->pacman->ghost->y] == '.')
		{
			pac->original_map[pac->pacman->ghost->x][pac->pacman->ghost->y] = ' ';
			pac->pacman->normal->x = normal.x;
			pac->pacman->normal->y = normal.y;
			pac->pac_points--;
			if (pac->pac_points == 0)
				ft_end_game(pac, 1);
		}
		else if (strchr("BYIC", pac->map[pac->pacman->ghost->x][pac->pacman->ghost->y]))
			ft_end_game(pac, 0);
		else
		{
			pac->pacman->old = pac->map[pac->pacman->ghost->x][pac->pacman->ghost->y];
			pac->map[pac->pacman->ghost->x][pac->pacman->ghost->y] = 'P';
			pac->pacman->normal->x = normal.x;
			pac->pacman->normal->y = normal.y;
		}
	}
}

void	ft_get_normal(t_vect2d *normal, t_vect2d *src, t_vect2d *dest)
{
	t_vect2d	diff;

	ft_vect_dif(&diff, src, dest);
	if (diff.x == 0 && diff.y == 0)
	{
		normal->x = 1;
		normal->y = 0;
		return ;
	}
	if (abs(diff.x) >= abs(diff.y))
	{
		normal->x = diff.x / abs(diff.x);
		normal->y = 0;
	}
	else
	{
		normal->x = 0;
		normal->y = diff.y / abs(diff.y);	
	}
}

void	ft_get_second_normal(t_vect2d *normal, t_vect2d *src, t_vect2d *dest)
{
	t_vect2d	diff;

	ft_vect_dif(&diff, src, dest);
	if (diff.x == 0 || diff.y == 0)
	{
		normal->x = 0;
		normal->y = 0;
		return ;
	}
	if (abs(diff.x) >= abs(diff.y))
	{
		normal->x = 0;
		normal->y = diff.y / abs(diff.y);
	}
	else
	{
		normal->x = diff.x / abs(diff.x);
		normal->y = 0;	
	}	
}

void	ft_get_random_normal(t_vect2d *normal)
{
	int	r;

	r = rand() % 4;
	if (r == 0)
	{
		normal->x = 1;
		normal->y = 0;
	}
	else if (r == 1)
	{
		normal->x = -1;
		normal->y = 0;
	}
	else if (r == 2)
	{
		normal->x = 0;
		normal->y = 1;
	}
	else if (r == 3)
	{
		normal->x = 0;
		normal->y = -1;
	}
}

void	ft_move_blinky_dumb(t_pacman *pac)
{
	t_vect2d	normal;

	if (pac->blinky->ghost == NULL)
		return ;
	ft_get_normal(&normal, pac->blinky->ghost, pac->pacman->ghost);
	if (ft_can_move(pac, pac->blinky->ghost, &normal) == 0)
		ft_get_second_normal(&normal, pac->blinky->ghost, pac->pacman->ghost);
	if (ft_can_move(pac, pac->blinky->ghost, &normal))
	{
		if (pac->blinky->old)
			pac->map[pac->blinky->ghost->x][pac->blinky->ghost->y] = pac->blinky->old;
		else
			pac->map[pac->blinky->ghost->x][pac->blinky->ghost->y] = ' ';
		pac->blinky->ghost->x += normal.x;
		pac->blinky->ghost->y += normal.y;
		if (pac->map[pac->blinky->ghost->x][pac->blinky->ghost->y] == 'P')
			ft_end_game(pac, 0);
		pac->blinky->old = pac->map[pac->blinky->ghost->x][pac->blinky->ghost->y];
		//pac->map[pac->blinky->ghost->x][pac->blinky->ghost->y] = 'B';
		pac->blinky->normal->x = normal.x;
		pac->blinky->normal->y = normal.y;
	}
}

void	ft_move_pinky_dumb(t_pacman *pac)
{
	t_vect2d	normal;
	t_vect2d	dest;

	if (pac->pinky->ghost == NULL)
		return ;
	ft_vect_mult_scal(&dest, pac->pacman->normal, 3);
	ft_vect_sum(&dest, &dest, pac->pacman->ghost);
	ft_get_normal(&normal, pac->pinky->ghost, &dest);
	if (ft_can_move(pac, pac->pinky->ghost, &normal) == 0)
		ft_get_second_normal(&normal, pac->pinky->ghost, &dest);
	if (ft_can_move(pac, pac->pinky->ghost, &normal))
	{
		if (pac->pinky->old)
			pac->map[pac->pinky->ghost->x][pac->pinky->ghost->y] = pac->pinky->old;
		else
			pac->map[pac->pinky->ghost->x][pac->pinky->ghost->y] = ' ';
		pac->pinky->ghost->x += normal.x;
		pac->pinky->ghost->y += normal.y;
		if ( pac->map[pac->pinky->ghost->x][pac->pinky->ghost->y] == 'P')
			ft_end_game(pac, 0);
		pac->pinky->old = pac->map[pac->pinky->ghost->x][pac->pinky->ghost->y];
		if (ft_vect_eql(pac->pinky->ghost, pac->blinky->ghost))
			pac->pinky->old = pac->blinky->old;
		//pac->map[pac->pinky->ghost->x][pac->pinky->ghost->y] = 'Y';
		pac->pinky->normal->x = normal.x;
		pac->pinky->normal->y = normal.y;
	}
}

void	ft_get_blinkys_target(t_pacman *pac, t_vect2d *target)
{
	if (!target || !pac || pac->playing == 0)
		return ;
	if (!pac->blinky->ghost)
	{
		target->x = 1;
		target->y = 1;
		return ;
	}
	target->x = pac->pacman->ghost->x;
	target->y = pac->pacman->ghost->y;
}

void	ft_get_pinkys_target(t_pacman *pac, t_vect2d *target)
{
	if (!target || !pac)
		return ;
	if (!pac->pinky->ghost)
	{
		target->x = 1;
		target->y = 1;
		return ;
	}
	target->x = pac->pacman->ghost->x + 4 * pac->pacman->normal->x;
	target->y = pac->pacman->ghost->y + 4 * pac->pacman->normal->y;
}

void	ft_get_inkys_target(t_pacman *pac, t_vect2d *target)
{
	t_vect2d	tmp;

	if (!target || !pac)
		return ;
	if (!pac->inky->ghost)
	{
		target->x = 1;
		target->y = 1;
		return ;
	}
	if (!pac->blinky->ghost)
	{
		target->x = pac->pacman->ghost->x;
		target->y = pac->pacman->ghost->y;
		return ;
	}
	tmp.x =  pac->pacman->ghost->x + 2 * pac->pacman->normal->x;  // 2(tmp - B) + B = 2tmp - B  
	tmp.y =  pac->pacman->ghost->y + 2 * pac->pacman->normal->y;  //tmp is two blocks ahead pacman 
	target->x = 2 * tmp.x - pac->blinky->ghost->x;				  //and B is the position of blinky
	target->y = 2 * tmp.y - pac->blinky->ghost->y; 
}

void	ft_get_clydes_target(t_pacman *pac, t_vect2d *target)
{
	if (!target || !pac)
		return ;
	if (!pac->clyde->ghost || ft_distance(pac->pacman->ghost, pac->clyde->ghost) < 8)
	{
		target->x = 1;
		target->y = 1;
		return ;
	}
	target->x = pac->pacman->ghost->x;
	target->y = pac->pacman->ghost->y;
}

void	ft_next_step(t_pacman *pac, t_ghost *ghost, void (*get_target)(t_pacman *, t_vect2d *))
{
	t_list		*path;
	t_vect2d	target;
	t_anode		*next_node;


	if (!ghost || !ghost->ghost || pac->playing == 0)
		return;
	get_target(pac, &target);
	path = ft_astar(pac->astar_map, ghost->ghost ,&target);
	if (path == NULL || path->content == NULL)
	{
		ft_get_random_normal(ghost->normal);
		return ;
	}
	next_node = path->next->content;
	ft_vect_dif(ghost->normal, ghost->ghost, &next_node->pos);
	ft_lstclear(&path, ft_free_anode);
}

void	ft_move_clyde_dumb(t_pacman *pac)
{
		t_vect2d	normal;

	if (pac->clyde->ghost == NULL)
		return ;
	ft_get_random_normal(&normal);
	if (ft_can_move(pac, pac->clyde->ghost, &normal))
	{
		if (pac->clyde->old)
			pac->map[pac->clyde->ghost->x][pac->clyde->ghost->y] = pac->clyde->old;
		else
			pac->map[pac->clyde->ghost->x][pac->clyde->ghost->y] = ' ';
		pac->clyde->ghost->x += normal.x;
		pac->clyde->ghost->y += normal.y;
		if ( pac->map[pac->clyde->ghost->x][pac->clyde->ghost->y] == 'P')
			ft_end_game(pac, 0);
		pac->clyde->old = pac->map[pac->clyde->ghost->x][pac->clyde->ghost->y];
		if (ft_vect_eql(pac->clyde->ghost, pac->inky->ghost))
			pac->clyde->old = pac->inky->old;
		if (ft_vect_eql(pac->clyde->ghost, pac->pinky->ghost))
			pac->clyde->old = pac->pinky->old;
		if (ft_vect_eql(pac->clyde->ghost, pac->blinky->ghost))
			pac->clyde->old = pac->blinky->old;
		//pac->map[pac->clyde->ghost->x][pac->clyde->ghost->y] = 'C';
		pac->clyde->normal->x = normal.x;
		pac->clyde->normal->y = normal.y;
	}
}

void	ft_move_inky_dumb(t_pacman *pac)
{
	t_vect2d	normal;

	if (pac->inky->ghost == NULL)
		return ;
	if (pac->inky->normal->x == pac->inky->normal->y)
		ft_get_random_normal(&normal);
	else
	{
		normal.x = pac->inky->normal->x;
		normal.y = pac->inky->normal->y;
	}
	if (ft_can_move(pac, pac->inky->ghost, &normal))
	{
		if (pac->inky->old)
			pac->map[pac->inky->ghost->x][pac->inky->ghost->y] = pac->inky->old;
		else
			pac->map[pac->inky->ghost->x][pac->inky->ghost->y] = ' ';
		pac->inky->ghost->x += normal.x;
		pac->inky->ghost->y += normal.y;
		if ( pac->map[pac->inky->ghost->x][pac->inky->ghost->y] == 'P')
			ft_end_game(pac, 0);
		pac->inky->old = pac->map[pac->inky->ghost->x][pac->inky->ghost->y];
		if (ft_vect_eql(pac->inky->ghost, pac->pinky->ghost))
			pac->inky->old = pac->pinky->old;
		if (ft_vect_eql(pac->inky->ghost, pac->blinky->ghost))
			pac->inky->old = pac->blinky->old;
		//pac->map[pac->inky->ghost->x][pac->inky->ghost->y] = 'I';
		pac->inky->normal->x = normal.x;
		pac->inky->normal->y = normal.y;
	}
	else
		ft_get_random_normal(pac->inky->normal);
}

/*******************end move ******************/
/******************move ghosts ****************/
void	ft_move_ghost(t_pacman *pac, t_ghost *ghost)
{
	if (ft_can_move(pac, ghost->ghost, ghost->normal))
	{
		ghost->ghost->x += ghost->normal->x;
		ghost->ghost->y += ghost->normal->y;
		if (ft_vect_eql(pac->pacman->ghost, ghost->ghost))
			ft_end_game(pac, 0);
	}
}

void	*ft_move_blinky(void *args)
{
	t_pacman *pac;

	pac = (t_pacman *)args;
	if (pac == NULL || pac->blinky->ghost == NULL)
		return (NULL);
	ft_usleep(1000);
	while (pac->playing)
	{
		ft_next_step(pac, pac->blinky, ft_get_blinkys_target);
		ft_move_ghost(pac, pac->blinky);
		if (MODE)
			ft_sleep(SLEEP_GHOSTS_S);
		else
			ft_usleep(SLEEP_GHOSTS);
	}
	return (NULL);
}

void	*ft_move_pinky(void *args)
{
	t_pacman *pac;

	pac = (t_pacman *)args;
	if (pac == NULL || pac->pinky->ghost == NULL)
		return (NULL);
	ft_usleep(1000);
	while (pac->playing)
	{
		ft_next_step(pac, pac->pinky, ft_get_pinkys_target);
		ft_move_ghost(pac, pac->pinky);
		if (MODE)
			ft_sleep(SLEEP_GHOSTS_S);
		else
			ft_usleep(SLEEP_GHOSTS);
	}
	return (NULL);
}

void	*ft_move_inky(void *args)
{
	t_pacman *pac;

	pac = (t_pacman *)args;
	if (pac == NULL || pac->inky->ghost == NULL)
		return (NULL);
	ft_usleep(1000);
	while (pac->playing)
	{
		ft_next_step(pac, pac->inky, ft_get_inkys_target);
		ft_move_ghost(pac, pac->inky);
		if (MODE)
			ft_sleep(SLEEP_GHOSTS_S);
		else
			ft_usleep(SLEEP_GHOSTS);
	}
	return (NULL);
}

void	*ft_move_clyde(void *args)
{
	t_pacman *pac;

	pac = (t_pacman *)args;
	if (pac == NULL || pac->clyde->ghost == NULL)
		return (NULL);
	ft_usleep(1000);
	while (pac->playing)
	{
		ft_next_step(pac, pac->clyde, ft_get_clydes_target);
		ft_move_ghost(pac, pac->clyde);
		if (MODE)
			ft_sleep(SLEEP_GHOSTS_S);
		else
			ft_usleep(SLEEP_GHOSTS);
	}
	return (NULL);
}

void	*ft_display_thread(void *args)
{
	t_pacman	*pac;

	pac = (t_pacman *)args;
	ft_print_map(pac);
	ft_usleep(1000);
	while (pac->playing != 0)
	{
		ft_print_map(pac);
		ft_usleep(SLEEP_DISPLAY);
	}
	return (NULL);
}

void	*pacman_thread(void *args)
{
	t_pacman	*pac;
	char		c;

	pac = (t_pacman *)args;
	while (pac->playing)
	{
		c = getc(stdin);
		if (strchr("wsdzq", c) == NULL)
			continue ;
		ft_move_pacman(pac, c);
		ft_usleep(SLEEP_PACMAN);
	}
	return (NULL);
}

void	ft_cancel_threads(t_pacman *pac)
{
	if (pac->pacman->ghost)
		pthread_cancel(*pac->pacman->ghost_th);
	if (pac->blinky->ghost_th)
		pthread_cancel(*pac->blinky->ghost_th);
	if (pac->pinky->ghost)
		pthread_cancel(*pac->pinky->ghost_th);
	if (pac->inky->ghost)
		pthread_cancel(*pac->inky->ghost_th);
	if (pac->clyde->ghost)
		pthread_cancel(*pac->clyde->ghost_th);
}
/****************end move ghosts **************/
/*******************level********************/
void	ft_level(FILE *infile)
{
	t_pacman	pac;

	ft_init_level(&pac);
	ft_get_map(&pac, infile);
	ft_get_astar_map(&pac);
	ft_get_enteties(&pac);
	ft_dup_original_map(&pac);
	ft_print_map(&pac);
	if (pthread_create(pac.screen_th, NULL, ft_display_thread, &pac) != 0)
			ft_exit("Error : could not create screen thread \n", stderr, 1);
	if (pthread_create(pac.pacman->ghost_th, NULL, pacman_thread, &pac) != 0)
			ft_exit("Error : could not create the pacman thread !\n", stderr, 1);
	if (pthread_create(pac.blinky->ghost_th, NULL, ft_move_blinky, &pac) != 0)
			ft_exit("Error : could not create the blinky's thread !\n", stderr, 1);
	if (pthread_create(pac.pinky->ghost_th, NULL, ft_move_pinky, &pac) != 0)
			ft_exit("Error : could not create the pinky's thread !\n", stderr, 1);
	if (pthread_create(pac.inky->ghost_th, NULL, ft_move_inky, &pac) != 0)
			ft_exit("Error : could not create the inky's thread !\n", stderr, 1);
	if (pthread_create(pac.clyde->ghost_th, NULL, ft_move_clyde, &pac) != 0)
			ft_exit("Error : could not create the clyde's thread !\n", stderr, 1);
	pthread_join(*pac.pacman->ghost_th, NULL);
	pthread_join(*pac.blinky->ghost_th, NULL);
	pthread_join(*pac.pinky->ghost_th, NULL);
	pthread_join(*pac.inky->ghost_th, NULL);
	pthread_join(*pac.clyde->ghost_th, NULL);
	pthread_join(*pac.screen_th, NULL);
	ft_free_pac(&pac);
}

void	ft_level_single_thread(FILE *infile)
{
		t_pacman	pac;
		char		c;

	ft_init_level(&pac);
	ft_get_map(&pac, infile);
	ft_get_astar_map(&pac);
	ft_get_enteties(&pac);
	ft_dup_original_map(&pac);
	ft_print_map(&pac);
	while (pac.pacman->ghost && pac.playing)
	{		
		c = getc(stdin);
		if (c == EOF)
		{
			if (ferror(stdin) != 0)
				pac.quit = 40;
			else
				pac.quit = 41;
			break ;
		}
		if (strchr(CTRL_STIRNG, c))
		{
			ft_move_pacman(&pac, c);
			ft_next_step(&pac, pac.blinky, ft_get_blinkys_target);
			ft_move_ghost(&pac, pac.blinky);
			ft_next_step(&pac, pac.pinky, ft_get_blinkys_target);
			ft_move_ghost(&pac, pac.pinky);
			ft_next_step(&pac, pac.inky, ft_get_blinkys_target);
			ft_move_ghost(&pac, pac.inky);
			ft_next_step(&pac, pac.clyde, ft_get_blinkys_target);
			ft_move_ghost(&pac, pac.clyde);
			ft_print_map(&pac);
			ft_usleep(10);
		}

	}
	ft_free_pac(&pac);
	if (pac.quit != 0)
		ft_exit("Error : an error has accured (level not completed maybe...) !\n", stderr, pac.quit);
}

/*****************end level *****************/

int main(int argc, char **argv)
{
	int		i;
	char	*input = "level/1.txt";
	FILE	*infile;

	i = 1;
	do
	{
		if (argc > 1)
			input = argv[i++];
		infile = fopen(input, "r");
		if (infile == NULL)
			ft_exit("Error : could not read input file \n", stderr, 39);
		if (SINGLE_THREAD)
			ft_level_single_thread(infile);
		else
			ft_level(infile);
		fclose(infile);
	}
	while (i < argc);

    return 0;
}
//TODO:
/**
 * @todo	add inky behaviour
			check for leaks
			tune timing for the tests 
 */