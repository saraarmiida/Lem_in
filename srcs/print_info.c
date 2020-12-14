#include "../includes/lem_in.h"

void	print_room_visu(t_room *room)
{
	ft_printf("#n|x%d|y%d|v%d|l%d|%s|c1|\n",\
	room->x, room->y, room->visited, room->level, room->name);
}

void	print_edge_visu(t_rlink *edge, char c)
{
	ft_putstr("#");
	ft_putchar(c);
	ft_putstr("|fx");
	ft_putnbr(edge->opp->tgtroom->x);
	ft_putstr("|fy");
	ft_putnbr(edge->opp->tgtroom->y);
	ft_putstr("|tx");
	ft_putnbr(edge->tgtroom->x);
	ft_putstr("|ty");
	ft_putnbr(edge->tgtroom->y);
	ft_putstr("|f%d");
	ft_putnbr(edge->flow);
	ft_putstr("\n");
}

void	print_set(t_bucket *set)
{
	t_paths	*paths;
	t_path	*path;
	int		i;

	i = 1;
	paths = set->paths;
	ft_printf("\nPRINTING SET\n");
	ft_printf("#cost: %d\nflow: %d\nsteps: %d\n",\
	set->cost, set->flow, set->length);
	while (paths != NULL)
	{
		path = paths->path;
		ft_printf("Path%d length %d:\n", i, paths->length);
		while (path != NULL)
		{
			ft_printf("	Room %s (level: %d)\n",\
			path->room->name, path->room->level);
			path = path->next;
		}
		paths = paths->next;
		i++;
	}
}

void	print_path(t_bucket *set)
{
	t_paths	*paths;
	t_path	*path;
	int		i;

	i = 1;
	paths = set->paths;
	ft_printf("\n#PRINTING SET\n");
	ft_printf("#cost: %d\nflow: %d\nsteps: %d\n", set->cost, set->flow, set->length);
	while (paths != NULL)
	{
		path = paths->path;
		ft_printf("#Path%d length %d:\n", i, paths->length);
		while (path != NULL)
		{
			ft_printf("#Room %s (level: %d)\n", path->room->name, path->room->level);
			if (path->next != NULL)
				ft_printf("#f|fx%d|fy%d|tx%d|ty%d\n", path->room->x, path->room->y, path->next->room->x, path->next->room->y);
			path = path->next;
		}
		paths = paths->next;
		i++;
	}
}

void	print_rooms(t_lem *lem)
{
	int		i;
	t_room	*r;

	ft_printf("#Rooms:\n");
	i = 0;
	while (i < lem->tablesize)
	{
		r = lem->rooms[i];
		if (r != NULL)
		{
			ft_printf("#n|x%d|y%d|v%d|l%d|%s|c1|\n", r->x, r->y, r->visited, r->level, r->name);
			while (r->next != NULL)
			{
				r = r->next;
				ft_printf("#n|x%d|y%d|v%d|l%d|%s|c1|\n", r->x, r->y, r->visited, r->level, r->name);
			}
		}
		i++;
	}
	ft_printf("\n\n");
}

void	print_queue(t_queue *queue, int l)
{
	t_queue *q;

	q = queue;
	ft_printf("#queue l %d: ", l);
	while (q != NULL)
	{
		ft_printf("#| %s ", q->edge->tgtroom->name);
		q = q->next;
	}
	ft_printf("\n");
}
