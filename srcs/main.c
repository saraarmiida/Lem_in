#include "../includes/lem_in.h"

/*
** Print debug info
*/

void		print_rooms(t_lem *lem)
{
	int		i;
	int		j;
	t_room	*r;
	t_rlink	*rl;

	i = 0;
	while (i < lem->room_amount)
	{
		r = lem->rooms[i];
		j = 0;
		ft_printf("Name: %d | X: %d | Y: %d | Next: %p | Level: %d\n", r->name, r->x, r->y, r->next, r->level);
		while (r->links[j]->from != NULL)
		{
			ft_printf("\tLink pointer: %p | from: %s | to: %s | visited: %d\n", r->links[j], r->links[j]->from, r->links[j]->to, r->links[j]->visited);
			j++;
		}
		rl = r->linked_rooms;
		ft_printf("\tLinked rooms: ");
		while (rl != NULL)
		{
			ft_printf("%s -> ", rl->room->c_name);
			rl = rl->next;
		}
		ft_printf("\n");
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
	bfs(lem);
	print_debug_info(lem);
	send_ants(lem);
	return (0);
}
