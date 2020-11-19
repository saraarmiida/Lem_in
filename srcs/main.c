#include "../includes/lem_in.h"

int			main(void)
{
	t_lem	*lem;
	int		info;

	info = 1;
	if (!(lem = (t_lem*)malloc(sizeof(t_lem))))
		return (1);
	// if (argc == 3)
	// {
	// 	if (ft_strncmp(argv[2], "-v", 2) != 0)
	// 	{
	// 		ft_putstr_fd("Usage with file and visualiser: ./lem-in [map] -v | ./visualiser/visu\n", 2);
	// 		exit(0);
	// 	}
	// 	info = 1;
	// }
	// else if (argc != 2)
	// {
	// 	ft_putstr_fd("Usage: ./lem-in [map]\nWith visualiser: ./lem-in [map] -v | ./visualiser/visu\n", 2);
	// 	exit(0);
	// }
	// lem->fd = open(argv[1], O_RDONLY);
	lem->fd = 0;
	init_lem(lem);
	lem->info = info;
	read_input(lem);
	if (solve(lem) == 1)
	{
		ft_error("no possible paths");
		ft_printf("Couldn't solve\n");
	}
	//print_final_paths(lem);
	//if (lem->info == 1)
	//	print_debug_info(lem);
	send_ants(lem);
	return (0);
}
