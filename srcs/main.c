#include "../includes/lem_in.h"

int			main(int argc, char **argv)
{
	t_lem	*lem;

	if (!(lem = (t_lem*)malloc(sizeof(t_lem))))
		ft_error(strerror(errno));
	init_lem(lem);
	handle_flags(argc, argv, lem);
	read_input(lem);
	if (lem->info == 1)
		ft_printf("|-\t-|Rooms: %d Links: %d\n", lem->room_nb, lem->link_nb);
	if (solve(lem) == 1)
		ft_error("no possible paths");
	send_ants(lem);
	if (lem->leaks == 1)
		while (1)
			lem->leaks = 1;
	return (0);
}
