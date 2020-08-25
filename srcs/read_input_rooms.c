#include "../includes/lem_in.h"

/*
** create a room to be saved in struct
** - save hash value instead of room name
*/

int		is_double(t_lem *lem, int i)
{
	int j;

	j = 0;
	while (j < lem->room_amount)
	{
		if(ft_strstr(lem->rooms[j]->name, &lem->input[i]) != NULL)
		{
			ft_printf("Found a double");
			return (1);
		}
		j++;
	}
	ft_printf("Room is not a double");
	return (0);
}

int		save_room(t_lem *lem, int i, int j, int start_or_end)
{
	t_room	*room;

	if(is_double(lem, i) == 1)
		return(0);
	if (!(room = (t_room*)malloc(sizeof(t_room))))
		return (0);
	room->name = ft_strcdup(&lem->input[i], ' ');
	i += ft_strlen(room->name) + 1;
	room->x = ft_atoi(&lem->input[i]);
	i += ft_intlen(room->x) + 1;
	room->y = ft_atoi(&lem->input[i]);
	lem->rooms[j] = room;
	if (start_or_end == 1)
		lem->start = room;
	if (start_or_end == 2)
		lem->end = room;
	return (i + ft_intlen(room->y) + 1);
}

/*
** save start and end rooms
*/

int		get_start_and_end(t_lem *lem)
{
	int		i;
	char	*tempstart;
	char	*tempend;

	i = 0;
	if ((tempstart = ft_strstr(lem->input, "##start\n")) != NULL)
	{
		while(tempstart[i] != '\n')
			i++;
		save_room(lem, i++, 0, 1);
	}
	i = 0;
	if ((tempend = ft_strstr(lem->input, "##end\n")) != NULL)
	{
		while(tempend[i] != '\n')
			i++;
		save_room(lem, i++, 1, 2);
	}
	if (lem->start == NULL || lem->end == NULL)
		return (0);
	return (1);
}

/*
** validates room syntax
** - no rooms with same name
** - no rooms with same coordinate
** - add error message
*/

int		check_room(t_lem *lem, int i)
{
	int j;

	j = i;
	while (lem->input[j] != '\n' && lem->input[j])
	{
		if (lem->input[j] == '-')
			return (-1);
		j++;
	}
	while (ft_isprint(lem->input[i]) && lem->input[i] != ' ')
		i++;
	if (lem->input[i] != ' ')
		return (-2);
	i++;
	while (ft_isdigit(lem->input[i]))
		i++;
	if (lem->input[i] != ' ')
		return (-2);
	i++;
	while (ft_isdigit(lem->input[i]))
		i++;
	if (lem->input[i] != '\n')
		return (-2);
	lem->room_amount++;
	return (i + 1);
}

/*
** first count how many rooms and then save rooms to struct
** - error in case of wrongly formatted or duplicate room
** - save first linked list and afterwards reassign to t_room** when amount known?
** - save hash values instead of room names
** - chop shorter
** - save start and end rooms somehow
** - chop
*/

int		get_rooms(t_lem *lem)
{
	int	i;
	int	j;

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
			{
				ft_printf("Rooms error\n");
				return (1);
			}
		}
	}
	ft_printf("Got %d rooms\n", lem->room_amount);
	if (!(lem->rooms = (t_room**)malloc(sizeof(t_room) * lem->room_amount)))
		return (1);
	i = lem->i;
	j = 0;
	while (j < lem->room_amount)
	{
		if (lem->input[i] == '#')
			i = skip_line(lem->input, i);
		else
		{
			i = save_room(lem, i, j, 0);
			j++;
		}
	}
	lem->i = i;
	return (0);
}