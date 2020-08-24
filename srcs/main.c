#include "../includes/lem_in.h"

void	init_lem(t_lem *lem)
{
	lem->fd = 0;
	lem->ants = 0;
	lem->links = 0;
	lem->room_amount = 0;
	lem->link_amount = 0;
	lem->input = NULL;
}

int		main(void)
{
	t_lem	*lem;

	if (!(lem = (t_lem*)malloc(sizeof(t_lem))))
		return (1);
	init_lem(lem);
	read_input(lem);
	return (0);
}
