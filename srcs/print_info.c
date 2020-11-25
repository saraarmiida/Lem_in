#include "../includes/lem_in.h"

/*
** Print debug info
*/

void		print_queue(t_queue *queue, int l)
{
	t_queue	*q;

	q = queue;
	ft_printf("queue l %d: ", l);
	while (q != NULL)
	{
		ft_printf("| %s ", q->edge->tgtroom->c_name);
		q = q->next;
	}
	ft_printf("\n");
}

void		print_path(t_bucket *set)
{
	t_paths		*temp_paths;
	t_path		*temp_path;
	int			i;

	i = 1;
	temp_paths = set->paths;
	ft_printf("\nPRINTING SET\n");
	ft_printf("cost: %d\nflow: %d\nsteps: %d\n", set->cost, set->flow, set->length);
	while (temp_paths != NULL)
	{
		temp_path = temp_paths->path;
		ft_printf("Path%d length %d:\n", i, temp_paths->length);
		while (temp_path != NULL)
		{
			ft_printf("	Room %s (level: %d)\n", temp_path->room->c_name, temp_path->room->level);
			temp_path = temp_path->next;
		}
		temp_paths = temp_paths->next;
		i++;
	}
}

void		print_rooms(t_lem *lem)
{
	int		i;
	t_room	*r;

	ft_printf("Rooms:\n");
	i = 0;
	while (i < lem->tablesize)
	{
		r = lem->rooms[i];
		if (r != NULL)
		{
			ft_printf("|-\t-|Name: %s | X: %d | Y: %d | L: %d | Visited: %d | Next: %p\n", r->c_name, r->x, r->y, r->level, r->visited, r->next);
			while (r->next != NULL)
			{
				r = r->next;
				ft_printf("|-\t-|Name: %s | X: %d | Y: %d | L: %d | Visited: %d | Next: %p\n", r->c_name, r->x, r->y, r->level, r->visited, r->next);
			}
		}
		i++;
	}
	ft_printf("\n\n");
}

void		print_hashtable(t_lem *lem)
{
	int		i;
	int		j;
	t_room	*room;

	i = 0;
	j = 0;
	while (i < lem->tablesize)
	{
		if (lem->rooms[i] != NULL)
		{
			room = lem->rooms[i];
			ft_printf("slot [%d]:\n", i);
			ft_printf("	name: %s\n", lem->rooms[i]->c_name);
			j++;
			while (room->next != NULL)
			{
				ft_printf("	name: %s\n", room->next->c_name);
				room = room->next;
				j++;
			}
		}
		i++;
	}
	ft_printf("room amount: %d printed: %d\n\n", lem->room_amount, j);
}

void		print_debug_info(t_lem *lem)
{
	// print_hashtable(lem);
	print_rooms(lem);
	// print_paths(lem);
}
