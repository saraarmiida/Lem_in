#include "../includes/lem_in.h"

t_route		*bfs(t_lem *lem)
{
	t_route	*route;

	if (!(route = (t_route*)malloc(sizeof(t_route))))
		return (NULL);
	if (lem->start)
		ft_printf("We have a start");
	return (route);
}