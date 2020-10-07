#include "../includes/lem_in.h"

/*
** Print debug info
*/

void		print_rooms(t_lem *lem)
{
	int		i;
	t_room	*r;
	t_rlink	*rl;

	i = 0;
	while (i < lem->tablesize)
	{
		r = lem->rooms[i];
		if (r != NULL)
		{
			ft_printf("Name: %s | X: %d | Y: %d | L: %d | Next: %d\n", r->c_name, r->x, r->y, r->level, r->next);
			rl = r->linked_rooms;
			ft_printf("\tLinked rooms: ");
			while (rl != NULL)
			{
				ft_printf("%s -> ", rl->room->c_name);
				rl = rl->next;
			}
			ft_printf("\n");
			while (r->next != NULL)
			{
				r = r->next;
				//ft_printf("Name: %s | X: %d | Y: %d | L: %d | Next: %d\n", r->c_name, r->x, r->y, r->level, r->next);
				rl = r->linked_rooms;
				ft_printf("\tLinked rooms: ");
				while (rl != NULL)
				{
					ft_printf("%s -> ", rl->room->c_name);
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
	t_paths	*path;
	t_path	*room;
	int		i;
	int		j;

	path = lem->paths;
	i = 0;
	while (path != NULL)
	{
		j = 0;
		room = path->path;
		ft_printf("Path %d, length %d:\n", i + 1, path->length);
		while (room != NULL)
		{
			ft_printf("	Room %s (level: %d)\n", room->room->c_name, room->room->level);
			room = room->next;
		}
		i++;
		ft_printf("\n\n");
		path = path->next;
	}
}

void		print_hashtable(t_lem *lem)
{
	int	i;

	i = 0;
	while (i < lem->tablesize)
	{
		if (lem->rooms[i] != NULL)
		{
			ft_printf("slot [%d]:\n", i);
			ft_printf("	name: %s\n", lem->rooms[i]->c_name);
			if (lem->rooms[i]->next != NULL)
				ft_printf("	name: %s\n", lem->rooms[i]->next->c_name);
		}
		i++;
	}
	ft_printf("\n\n");
}

void		print_debug_info(t_lem *lem)
{
	print_rooms(lem);
	print_paths(lem);
}

int		main(int argc, char **argv)
{
	t_lem	*lem;

	if (!(lem = (t_lem*)malloc(sizeof(t_lem))))
		return (1);
	if (argc == 2)
		lem->fd = open(argv[1], O_RDONLY);
	init_lem(lem);
	lem->visu_info = 1;
	read_input(lem);
	print_hashtable(lem);
	bfs(lem);
	print_debug_info(lem);
	send_ants(lem);
	return (0);
}
