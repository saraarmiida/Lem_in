#include "../includes/lem_in.h"

void	send_ants(t_lem *lem)
{
	int		ant;
	t_path	*path;
	t_path	*start;

	ft_printf("%s\n\n", lem->input); // add ignoring comments
	ant = 1;
	start = lem->paths->path;
	while (ant <= lem->ants)
	{
		path = start;
		while (path->room != lem->end)
		{
			if (path->room->ant != 0)
			{
				ft_printf("L%d-%s\n", path->room->ant, path->room->c_name);
				path->next->room->ant = path->room->ant;
				path->room->ant = 0;
			}
			path = path->next;
		}
		if (ant <= lem->ants)
		{
			ft_printf("L%d-%s\n", ant, start->room->c_name);
			start->room->ant = ant;
		}
		ant++;
		ft_printf("\n");
	}
	while (path->room)
	{
		ft_printf("L%d-%s\n", ant, path->room->c_name);
		if (path->room == lem->end)
			break ;
		path = path->next;
	}
}
