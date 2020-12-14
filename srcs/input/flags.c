/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spentti <spentti@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:18:47 by spentti           #+#    #+#             */
/*   Updated: 2020/12/14 13:18:50 by spentti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		print_flags(t_lem *lem, int lines)
{
	char	*str;

	str = NULL;
	if (lem->print_set == 1)
		print_set(lem->best_set);
	if (lem->print_lines == 1)
		ft_printf("lines: %d\n", lines);
	if (lem->required == 1)
	{
		str = ft_strstr(lem->input, "#Here is the number of lines required: ");
		if (str == NULL)
			str = "not available";
		else
			str = ft_strcdup(str + 39, '\n');
		ft_printf("number of lines required: %s\n", str);
	}
}

void		print_usage(void)
{
	ft_putstr_fd("\nusage: ./lem-in [option] < [map]\n", 2);
	ft_putstr_fd("options:\n", 2);
	ft_putstr_fd("	-h : get usage\n", 2);
	ft_putstr_fd("	-v : run with visualiser. Print flags are not compatible\
	with this.\n", 2);
	ft_putstr_fd("	-q : quiet mode\n", 2);
	ft_putstr_fd("	-l : print number of lines\n", 2);
	ft_putstr_fd("	-r : print number of lines required\n", 2);
	ft_putstr_fd("	-s : print paths\n", 2);
	ft_putstr_fd("	-m : mode for testing leaks\n\n", 2);
	exit(0);
}

int			get_flag(char c, t_lem *lem)
{
	if (c == 'l')
		lem->print_lines = 1;
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
	else if (c == 'm')
		lem->leaks = 1;
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
