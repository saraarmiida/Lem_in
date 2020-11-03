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
		ft_printf("| %s ", q->room->c_name);
		q = q->next;
	}
	ft_printf("\n");
}

void		print_path(t_paths *paths)
{
	t_paths		*temp_paths;
	t_path		*temp_path;
	int			i;

	i = 1;
	temp_paths = paths;
	ft_printf("\nPRINTING PATHS\n");
	while (temp_paths != NULL)
	{
		temp_path = temp_paths->path;
		ft_printf("Path:\n");
		while (temp_path != NULL)
		{
			ft_printf("	Room %s (level: %d)\n", temp_path->room->c_name, temp_path->room->level);
			temp_path = temp_path->next;
		}
		temp_paths = temp_paths->next;
	}
}

void		print_rooms(t_lem *lem)
{
	int		i;
	t_room	*r;
	t_rlink	*rl;

	ft_printf("Rooms:\n");
	i = 0;
	while (i < lem->tablesize)
	{
		r = lem->rooms[i];
		if (r != NULL)
		{
			ft_printf("|-\t-|Name: %s | X: %d | Y: %d | L: %d | Visited: %d | Next: %p\n", r->c_name, r->x, r->y, r->level, r->visited, r->next);
			rl = r->linked_rooms;
			// ft_printf("\tLinked rooms: ");
			// while (rl != NULL)
			// {
			// 	ft_printf("%s -> ", rl->tgtroom->c_name);
			// 	rl = rl->next;
			// }
			// ft_printf("\n");
			while (r->next != NULL)
			{
				r = r->next;
				ft_printf("|-\t-|Name: %s | X: %d | Y: %d | L: %d | Visited: %d | Next: %p\n", r->c_name, r->x, r->y, r->level, r->visited, r->next);
				rl = r->linked_rooms;
				// ft_printf("\tLinked rooms: ");
				// while (rl != NULL)
				// {
				// 	ft_printf("%s -> ", rl->tgtroom->c_name);
				// 	rl = rl->next;
				// }
				// ft_printf("\n");
			}
		}
		i++;
	}
	ft_printf("\n\n");
}

void		print_paths(t_lem *lem)
{
	t_bucket	*bucket;
	t_paths		*temp_paths;
	t_path		*temp_path;
	int			i;

	i = 1;
	bucket = lem->bucketlist;
	while (bucket->next_bucket != NULL)
	{
		ft_printf("\nBucket %d:\n", i);
		temp_paths = bucket->paths;
		while (temp_paths != NULL)
		{
			temp_path = temp_paths->path;
			ft_printf("Path:\n");
			while (temp_path != NULL)
			{
				ft_printf("	Room %s (level: %d)\n", temp_path->room->c_name, temp_path->room->level);
				temp_path = temp_path->next;
			}
			temp_paths = temp_paths->next;
		}
		i++;
		ft_printf("\n\n");
		bucket = bucket->next_bucket;
	}
}

void		print_hashtable(t_lem *lem)
{
	int	i;
	int j;
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
	//print_hashtable(lem);
	print_rooms(lem);
	// print_paths(lem);
}