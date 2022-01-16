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

	request.tv_sec = sec;
	request.tv_nsec = 0;
    nanosleep(&request, &remaining);
}

void	ft_usleep(int usec)
{
	struct timespec remaining, request;

	request.tv_sec = usec / 1000000;
	request.tv_nsec = usec % 1000000;
    nanosleep(&request, &remaining);
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
char	*get_next_line(FILE *file)
{
	char			*c;
	char			*out;
	t_list			*tmp;

	if (file == NULL)
		return (NULL);
	tmp = NULL;
	c = malloc(1);
	while ((*c = fgetc(file)) != EOF)
	{
		if (*c == '\n')
			break ;
		ft_lstadd_back(&tmp, ft_lstnew(c));
		c = malloc(1);
	}
	out = ft_ltoa(tmp);
	ft_lstclear(&tmp, free);
	return (out);
}

/***********end get next line **********/
/***********get level *******************/
t_ghost	*ft_newghost(int type)
{
	t_ghost	*out;

	out = malloc(sizeof(t_ghost));
	if (out == NULL)
		return (NULL);
	out->type = type;
	out->ghost = NULL;
	out->normal = ft_vectnew(0, 0);
	out->old = 0;
	return (out);
}

void	ft_init_level(t_pacman *pac)
{
	if (pac == NULL)
		return ;
	pac->pac_points = 0;
	pac->playing = 1;
	pac->ghosts_th = NULL;
	pac->map = NULL;
	pac->pacman = ft_newghost('P');
	pac->blinky = ft_newghost('B');
	pac->pinky = ft_newghost('Y');
	pac->inky = ft_newghost('I');
	pac->clyde = ft_newghost('C');
}

void	ft_get_map(t_pacman *pacman, FILE *input)
{
	t_list	*tmp;
	char	*line;
	char	**save;
	size_t	size;

	if (pacman == NULL || input == NULL)
		return ;
	line = get_next_line(input);
	tmp = NULL;
	while (line)
	{
		ft_lstadd_back(&tmp, ft_lstnew(line));
		line = get_next_line(input);
	}
	size = ft_lstsize(tmp) + 1;
	pacman->map = malloc(size * sizeof(char *));
	pacman->astar_map = malloc(size * sizeof(char *));
	if (pacman->map == NULL || pacman->astar_map == NULL)
		ft_exit("Error : could not allocate memory !\n", stderr, 1);
	save = pacman->map;
	while (tmp)
	{
		*save = (char *)tmp->content;
		save++;
		tmp = tmp->next;
	}
	*save = NULL;
	ft_lstclear(&tmp, NULL);
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

void	ft_print_map(t_pacman *pac)
{
	char	**map;

	system("clear");
	map = pac->map;
	while (*map)
		printf("%s\n", *map++);
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
					ft_exit("Error : there should be only one pacman !\n", stderr, 1);
				pac->pacman->ghost = ft_vectnew(i, j);
			}
			else if (tmp[i][j] == 'B' && pac->blinky->ghost == NULL)
				pac->blinky->ghost = ft_vectnew(i, j);
			else if (tmp[i][j] == 'Y' && pac->pinky->ghost == NULL)
				pac->pinky->ghost = ft_vectnew(i, j);
			else if (tmp[i][j] == 'I' && pac->inky->ghost == NULL)
				pac->inky->ghost = ft_vectnew(i, j);
			else if (tmp[i][j] == 'C' && pac->clyde->ghost == NULL)
				pac->clyde->ghost = ft_vectnew(i, j);
			else if (tmp[i][j] == '.')
				pac->pac_points++;
			j++;
		}
		i++;
	}
}

void	ft_end_game(t_pacman *pac, int succ)
{
	pac->playing = 0;
	ft_usleep(10000);
	if (succ == 1)
	{
		ft_print_map(pac);
		printf("\nYou have won !\n");
	}
	if (succ == 2)
	{
		ft_print_map(pac);
		printf("\nYou have quited the game !\n");
	}
	if (succ == 0)
	{
		ft_print_map(pac);
		printf("\nyou have been eaten !\n");
	}
}

void	ft_free_ghost(t_ghost **ghost)
{
	if (!ghost || !*ghost)
		return ;
	if ((*ghost)->ghost)
		free((*ghost)->ghost);
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
	while (pac->map[i])
		free(pac->map[i++]);
	free(pac->map);
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

void	ft_free_null(void *node)
{
	(void)node; //don't do anything 
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
	printf("getting path :\n");
	while (current)
	{
		ft_lstadd_front(&out, ft_lstnew(ft_node_dup(current)));
		father.pos.x = current->father.x;
		father.pos.y = current->father.y;
		printf("current : (%d, %d) father : (%d, %d)\n", current->pos.x, current->pos.y, current->father.x, current->father.y);
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
		ft_lstremove_one(&open, current, ft_anode_pos_eql, ft_free_null); // can optimize here !
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
					while (++i < 4)
						free(neighbor[i]);
					// free lists
					return (out);
				}
				if (ft_lst_in(closed, neighbor[i], ft_anode_pos_eql) && ++i)
					continue ;
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
					ft_lstadd_back(&open, ft_lstnew(neighbor[i]));		
			}
			i++;
		}
		ft_lstadd_back(&closed, ft_lstnew(current));	
	}
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

void	ft_move_pacman(t_pacman *pac)
{
	char		c;
	t_vect2d 	normal;

	c = getc(stdin);

	if (c == 'z' || c == 'Z')
	{			
		normal.y = 0;
		normal.x = -1;
	}
	else if (c == 's' || c == 'S')
	{
		normal.y = 0;
		normal.x = 1;
	}
	else if (c == 'w' || c == 'W')
	{
		normal.y = -1;
		normal.x = 0;
	}
	else if (c == 'd' || c == 'D')
	{
		normal.y = 1;
		normal.x = 0;
	}
	else if (c == 'q' || c == 'Q')
		ft_end_game(pac, 2);
	else
		return ;
	if (ft_can_move(pac, pac->pacman->ghost, &normal))
	{
		if (pac->pacman->old)
			pac->map[pac->pacman->ghost->x][pac->pacman->ghost->y] = pac->pacman->old;
		else
			pac->map[pac->pacman->ghost->x][pac->pacman->ghost->y] = ' ';
		pac->pacman->ghost->x += normal.x;
		pac->pacman->ghost->y += normal.y;
		if (pac->map[pac->pacman->ghost->x][pac->pacman->ghost->y] == '.')
		{
			pac->map[pac->pacman->ghost->x][pac->pacman->ghost->y] = 'P';
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
	printf("second \n");
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

void	ft_move_blinky(t_pacman *pac)
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
		if ( pac->map[pac->blinky->ghost->x][pac->blinky->ghost->y] == 'P')
			ft_end_game(pac, 0);
		pac->blinky->old = pac->map[pac->blinky->ghost->x][pac->blinky->ghost->y];
		pac->map[pac->blinky->ghost->x][pac->blinky->ghost->y] = 'B';
		pac->blinky->normal->x = normal.x;
		pac->blinky->normal->y = normal.y;
	}
}

void	ft_move_pinky(t_pacman *pac)
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
		pac->map[pac->pinky->ghost->x][pac->pinky->ghost->y] = 'Y';
		pac->pinky->normal->x = normal.x;
		pac->pinky->normal->y = normal.y;
	}
}

void	ft_move_clyde(t_pacman *pac)
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
		pac->map[pac->clyde->ghost->x][pac->clyde->ghost->y] = 'C';
		pac->clyde->normal->x = normal.x;
		pac->clyde->normal->y = normal.y;
	}
}

void	ft_move_inky(t_pacman *pac)
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
		pac->map[pac->inky->ghost->x][pac->inky->ghost->y] = 'I';
		pac->inky->normal->x = normal.x;
		pac->inky->normal->y = normal.y;
	}
	else
		ft_get_random_normal(pac->inky->normal);
}

void	ft_move_ghosts(t_pacman *pac)
{
	(void)pac;
	ft_move_blinky(pac);
	ft_move_pinky(pac);
	ft_move_inky(pac);
	//ft_move_clyde(pac);
	return ;
}

/*******************end move ******************/
/******************move ghosts ****************/

void	*ghost_thread(void *args)
{
	t_pacman	*pac;

	pac = (t_pacman *)args;
	ft_print_map(pac);
	while (pac->playing)
	{
		ft_sleep(1);
		ft_move_ghosts(pac);
		ft_print_map(pac);
	}
	return (NULL);
}


/****************end move ghosts **************/
void	ft_level(FILE *infile)
{
	t_pacman	pac;
	pthread_t	pth;

	ft_init_level(&pac);
	ft_get_map(&pac, infile);
	ft_get_enteties(&pac);
	pac.ghosts_th = &pth;
	if (pthread_create(&pth, NULL, ghost_thread, &pac) != 0)
			ft_exit("Error : could not create the ghosts thread !\n", stderr, 1);
	while (pac.playing)
	{
		ft_move_pacman(&pac);
		ft_print_map(&pac);
	}
	ft_free_pac(&pac);
}

/*
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
			ft_exit("Error : could not read input file \n", stderr, 1);
		ft_level(infile);
		fclose(infile);
	}
	while (i < argc);

    return 0;
}
*/

int main()
{
	t_list	*path;
	t_vect2d a;
	t_vect2d b;

	char **grid = malloc (11 * sizeof (char *));
	grid[0] =  strdup("000000000000");
	grid[1] =  strdup("010111101110");
	grid[2] =  strdup("011101110110");
	grid[3] =  strdup("011101111010");
	grid[4] =  strdup("000101001110");
	grid[5] =  strdup("011101110120");
	grid[6] =  strdup("010111101100");
	grid[7] =  strdup("010000101010");
	grid[8] =  strdup("010111101110");
	grid[9] =  strdup("011100010010");
	grid[10] = strdup("000000000000");

	a.x = 9;
	a.y = 10;
	b.x = 1;
	b.y = 1;
	path = NULL;
	path = ft_astar(grid, &a, &b);
	printf("path size %d\n", ft_lstsize(path));
	for (int i = 0; i < 9; i++)
	{
		free(grid[i]);
	}
	free(grid);
	return (0);
}