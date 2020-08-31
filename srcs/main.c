#include "../includes/lem_in.h"

/*
** Print debug info
*/

void		print_debug_info(t_lem *lem)
{
	int		i;
	int		j;
	t_room	*r;

	i = 0;
	j = 0;
	while(i < lem->room_amount)
	{
		r = lem->rooms[i];
		ft_printf("Name: %d | X: %d | Y: %d | Next: %p\n", r->name, r->x, r->y, r->next);
		while (r->links[j]->from != NULL)
		{
			ft_printf("\tLink pointer: %p | from: %s | to: %s | visited: %d\n", r->links[j], r->links[j]->from, r->links[j]->to, r->links[j]->visited);
			j++;
		}
		j = 0;
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_lem	*lem;

	if (!(lem = (t_lem*)malloc(sizeof(t_lem))))
		return (1);
	if (argc == 2)
		lem->fd = open(argv[1], O_RDONLY);
	init_lem(lem);
	read_input(lem);
	print_debug_info(lem);
	return (0);
}
