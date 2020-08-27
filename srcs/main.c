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
	make_hashtable(lem);
	return (0);
}
