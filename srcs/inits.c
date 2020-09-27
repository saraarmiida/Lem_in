#include "../includes/lem_in.h"

void	init_lem(t_lem *lem)
{
	lem->fd = 3;
	lem->ants = 0;
	lem->links = 0;
	lem->room_amount = 0;
	lem->link_amount = 0;
	lem->input = NULL;
	lem->j = 0;
	lem->visu_info = 0;
}

/*
** Allocate memory for links in a room and set the initial values
*/

int		init_links(t_room *room)
{
	int		i;

	i = 0;
	if (!(room->links = (t_llink**)malloc(sizeof(t_llink) * BAD_MAGIC_NUMBER_LINKS)))
	{
		ft_printf("Could not allocate links.");
		return (0);
	}
	while (i < BAD_MAGIC_NUMBER_LINKS)
	{
		if (!(room->links[i] = (t_llink*)malloc(sizeof(t_llink))))
			return (0);
		room->links[i]->from = NULL;
		room->links[i]->to = NULL;
		room->links[i]->visited = 0;
		i++;
	}
	return (1);
}

