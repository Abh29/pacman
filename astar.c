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

char	*ft_strdup(char *str)
{
	char	*out;
	int		i;

	out = malloc(strlen(str) + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (str[i])
		out[i] = str[i++];
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
	printf("getting path :\n");
	while (current)
	{
		ft_lstadd_front(&out, ft_lstnew(ft_node_dup(current)));
		father.pos.x = current->father.x;
		father.pos.y = current->father.y;
		printf("current : (%d, %d) father : (%d, %d)\n", current->pos.x, current->pos.y, \
		current->father.x, current->father.y);
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

int main()
{
	t_list	*path;
	t_vect2d a;
	t_vect2d b;

	char **grid = malloc (11 * sizeof (char *));
	grid[0] =  ft_strdup("000000000000");
	grid[1] =  ft_strdup("010111101110");
	grid[2] =  ft_strdup("011101110110");
	grid[3] =  ft_strdup("011101111010");
	grid[4] =  ft_strdup("000101001110");
	grid[5] =  ft_strdup("011101110120");
	grid[6] =  ft_strdup("010111101100");
	grid[7] =  ft_strdup("010000101010");
	grid[8] =  ft_strdup("010111101110");
	grid[9] =  ft_strdup("011100010010");
	grid[10] = ft_strdup("000000000000");

	a.x = 9;
	a.y = 10;
	b.x = 1;
	b.y = 1;
	path = NULL;
	path = ft_astar(grid, &a, &b);
	printf("path size %d\n", ft_lstsize(path));
	for (int i = 0; i < 11; i++)
	{
		free(grid[i]);
	}
	free(grid);
	ft_lstclear(&path, ft_free_anode);
	return (0);
}

//TODO:
/**
 * @todo	test Astar algorim , free lists check valgrind for leaks
 * 			check for leaks in the initial program
 * 			create a separate thread for each ghost and implement Astar
 */