#include "../includes/lem_in.h"

/*
** Print debug info
*/

void		print_debug_info(t_lem *lem)
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
		ft_printf("Name: %d | X: %d | Y: %d | Next: %p\n", r->name, r->x, r->y, r->next);
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
}

int		main(int argc, char **argv)
{
	t_lem	*lem;
	t_route	*testroute;

	if (!(lem = (t_lem*)malloc(sizeof(t_lem))))
		return (1);
	if (argc == 2)
		lem->fd = open(argv[1], O_RDONLY);
	init_lem(lem);
	read_input(lem);
	print_debug_info(lem);
	testroute = bfs(lem);
	return (0);
}
