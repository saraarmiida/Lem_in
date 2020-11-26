#include "../includes/lem_in.h"

void		print_usage(void)
{
	ft_putstr_fd("\nusage: ./lem-in [option] | ./visualiser/visu\n", 2);
	ft_putstr_fd("options:\n", 2);
	ft_putstr_fd("	-h : get usage\n", 2);
	ft_putstr_fd("	-v : run with visualiser\n", 2);
	ft_putstr_fd("	-q : quiet mode\n", 2);
	ft_putstr_fd("	-l : print number of lines\n", 2);
	ft_putstr_fd("	-r : print number of lines required\n", 2);
	ft_putstr_fd("	-s : print paths\n\n", 2);
	exit(0);
}

int			get_flag(char c, t_lem *lem)
{
	if (c == 'l')
		lem->print_links = 1;
	else if (c == 's')
		lem->print_set = 1;
	else if (c == 'h')
		print_usage();
	else if (c == 'v')
		lem->info = 1;
	else if (c == 'q')
		lem->quiet = 1;
	else if (c == 'r')
		lem->required = 1;
	else
		return (0);
	return (1);
}

void		handle_flags(int argc, char **argv, t_lem *lem)
{
	int	i;
	int	j;

	i = 1;
	if (argc > 1)
	{
		while (i < argc)
		{
			if (argv[i][0] == '-')
			{
				j = 1;
				while (argv[i][j])
				{
					if (get_flag(argv[i][j], lem) == 0)
						print_usage();
					j++;
				}
				i++;
			}
			else
				print_usage();
		}
	}
}

int			main(int argc, char **argv)
{
	t_lem	*lem;

	if (!(lem = (t_lem*)malloc(sizeof(t_lem))))
		ft_error(strerror(errno));
	init_lem(lem);
	handle_flags(argc, argv, lem);
	read_input(lem);
	if (lem->info == 1)
		ft_printf("|-\t-|Rooms: %d Links: %d\n", lem->room_amount, lem->link_amount);
	if (solve(lem) == 1)
		ft_error("no possible paths");
	send_ants(lem);
	return (0);
}
