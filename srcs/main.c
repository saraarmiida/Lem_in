#include "../includes/lem_in.h"

/*
** Print debug info
*/

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
			ft_printf("\tLinked rooms: ");
			while (rl != NULL)
			{
				ft_printf("%s -> ", rl->tgtroom->c_name);
				rl = rl->next;
			}
			ft_printf("\n");
			while (r->next != NULL)
			{
				r = r->next;
				ft_printf("|-\t-|Name: %s | X: %d | Y: %d | L: %d | Visited: %d | Next: %p\n", r->c_name, r->x, r->y, r->level, r->visited, r->next);
				rl = r->linked_rooms;
				ft_printf("\tLinked rooms: ");
				while (rl != NULL)
				{
					ft_printf("%s -> ", rl->tgtroom->c_name);
					rl = rl->next;
				}
				ft_printf("\n");
			}
		}
		i++;
	}
	ft_printf("\n\n");
}

void		print_paths(t_lem *lem)
{
	t_bucket	*bucket;
	t_path		*temp_path;
	int			i;

	i = 1;
	bucket = lem->bucketlist;
	while (bucket->next_bucket != NULL)
	{
		ft_printf("\nBucket %d:\n", i);
		while (bucket->path != NULL)
		{
			ft_printf("Path:\n");
			temp_path = bucket->path;
			while (temp_path != NULL)
			{
				ft_printf("	Room %s (level: %d)\n", temp_path->room->c_name, temp_path->room->level);
				temp_path = temp_path->next;
			}
			bucket->path = bucket->next_path;
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
	print_paths(lem);
}


int			main(int argc, char **argv)
{
	t_lem	*lem;
	int		info;

	info = 1;
	if (!(lem = (t_lem*)malloc(sizeof(t_lem))))
		return (1);
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "-v", 2) != 0)
		{
			ft_putstr_fd("Usage with file and visualiser: ./lem-in [map] -v | ./visualiser/visu\n", 2);
			exit(0);
		}
		info = 1;
	}
	else if (argc != 2)
	{
		ft_putstr_fd("Usage: ./lem-in [map]\nWith visualiser: ./lem-in [map] -v | ./visualiser/visu\n", 2);
		exit(0);
	}
	lem->fd = open(argv[1], O_RDONLY);
	init_lem(lem);
	lem->info = info;
	read_input(lem);
	if (lem->info == 1)
		ft_printf("|-\t-|Rooms: %d Links: %d\n", lem->room_amount, lem->link_amount);
	while (create_bucket(lem) == 1) {
		ft_printf("Made a bucket");
	}
	if (lem->info == 1)
		print_debug_info(lem);
	//send_ants(lem);
	return (0);
}
