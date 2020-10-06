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
	lem->paths =  NULL;
}
