#include "../includes/lem_in.h"

int		iterate_nodes(t_lem *lem)
{
	
}

void	bfs(t_lem *lem)
{
	if (!(lem->routes = (t_route**)malloc(sizeof(t_route) * lem->room_amount / 2)))
	{
		ft_printf("Malloc failed");
		return ;
	}
	if (lem->start)
		ft_printf("We have a start");
	if (iterate_nodes(lem) == 1)
		ft_printf("Nodes iterated");
}