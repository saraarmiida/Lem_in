#include "../includes/lem_in.h"

void	send_ants(t_lem *lem)
{
	int		ant;
	t_path	*path;

	ft_printf("%s\n\n", lem->input); // add ignoring comments
	ant = 1;
	path = lem->paths->path;
	while (path->room)
	{
		ft_printf("L%d-%s\n", ant, path->room->c_name);
		if (path->room == lem->end)
			break ;
		path = path->next;
	}
}
