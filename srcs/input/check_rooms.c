#include "../includes/lem_in.h"

static int		check_coordinate(t_lem *lem, int i)
{
	if (lem->input[i] != ' ')
		ft_error("invalid rooms");
	i++;
	if (lem->input[i] == '-')
		i++;
	while (ft_isdigit(lem->input[i]))
		i++;
	return (i);
}

/*
** validates room syntax
*/

static int		check_room(t_lem *lem, int i)
{
	int j;

	j = i;
	if (lem->input[i] == 'L' || lem->input[i] == '#')
		ft_error("invalid room name");
	while (lem->input[j] != '\n' && lem->input[j])
	{
		if (lem->input[j] == '-' && !(ft_isdigit(lem->input[j + 1]) == 1\
		&& lem->input[j - 1] == ' '))
			return (-1);
		j++;
	}
	while (ft_isprint(lem->input[i]) && lem->input[i] != ' ')
		i++;
	i = check_coordinate(lem, i);
	i = check_coordinate(lem, i);
	if (lem->input[i] != '\n')
		ft_error("invalid rooms");
	lem->room_nb++;
	return (i + 1);
}

void			check_rooms(t_lem *lem)
{
	int	i;

	i = lem->i;
	while (lem->input[i])
	{
		if (lem->input[i] == '#')
			i = skip_line(lem->input, i);
		else
		{
			if ((i = check_room(lem, i)) == -1)
				break ;
			else if (i == -2)
				ft_error("invalid rooms");
		}
	}
}
