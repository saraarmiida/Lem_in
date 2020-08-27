#include "../includes/lem_in.h"

/*
** ft_strmatchlen takes haystack and needle and
** returns the number of indexes the haystack had to
** search plus the length of needle. If needle is
** not found, it returns -1.
*/

int	ft_strmatchlen(char const *s, char const *s2)
{
	int i;
	int j;

	i = 0;
	while(s[i] != '\0')
	{
		j = 0;
		while (s[i] != s2[0] && s[i] != '\0')
			i++;
		while(s[i] == s2[j])
		{
			i++;
			j++;
		}
		if (s2[j] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

/*
** create a room to be saved in struct
** - save hash value instead of room name
*/

int		is_double(t_lem *lem, int j, int name)
{
	while (j >= 0)
	{
		if (lem->rooms[j]->name == name)
		{
			//ft_printf("Found a double\n");
			//ft_printf("Found a double\n");
			return (1);
		}
		j--;
	}
	//ft_printf("Room is not a double.\n");
	return (0);
}

int		save_room(t_lem *lem, int i, int j, int start_or_end)
{
	t_room	*room;
	int		name;

	name = ft_atoi(ft_strcdup(&lem->input[i], ' '));
	if (start_or_end == 0)
	{
		if(is_double(lem, j - 1, name) == 1)
		{
			lem->j = j;
			return(skip_line(lem->input, i));
		}
	}
	if (!(room = (t_room*)malloc(sizeof(t_room))))
		return (0);
	room->name = name;
	i += ft_intlen(room->name) + 1;
	room->x = ft_atoi(&lem->input[i]);
	i += ft_intlen(room->x) + 1;
	room->y = ft_atoi(&lem->input[i]);
	lem->rooms[j] = room;
	if (start_or_end == 1)
		lem->start = room;
	if (start_or_end == 2)
		lem->end = room;
	ft_printf("Name: %d | X: %d | Y: %d | Next: %p\n", room->name, room->x, room->y, room->next);
	lem->j = j + 1;
	return (i + ft_intlen(room->y) + 1);
}

/*
** save start and end rooms
*/

int		get_start_and_end(t_lem *lem)
{
	int		i;
	int		start;
	int		end;

	i = 0;
	start = ft_strmatchlen(lem->input, "##start\n");
	end = ft_strmatchlen(lem->input, "##end\n");
	if (start == -1 || end == -1)
		return (0);
	save_room(lem, start, 0, START_ROOM);
	save_room(lem, end, 1, END_ROOM);
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
	get_start_and_end(lem);
	i = lem->i;
	j = 2;
	while (j < lem->room_amount)
	{
		if (lem->input[i] == '#')
			i = skip_line(lem->input, i);
		else
		{
			i = save_room(lem, i, j, 0);
			j = lem->j;
		}
	}
	lem->i = i;
	return (0);
}