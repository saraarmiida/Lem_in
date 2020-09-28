#include "../includes/lem_in.h"

/*
** ft_strmatchlen takes haystack and needle and
** returns the number of indexes the haystack had to
** search plus the length of needle. If needle is
** not found, it returns -1.
*/

int		ft_strmatchlen(char const *s, char const *s2)
{
	int i;
	int j;

	i = 0;
	while (s[i] != '\0')
	{
		j = 0;
		while (s[i] != s2[0] && s[i] != '\0')
			i++;
		while (s[i] == s2[j])
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

t_room	*get_room_info(t_lem *lem, char *name, int i, int start_or_end)
{
	t_room	*room;

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		return (0);
	room->c_name = name;
	room->name = ft_atoi(name);
	i += ft_intlen(room->name) + 1;
	room->x = ft_atoi(&lem->input[i]);
	i += ft_intlen(room->x) + 1;
	room->y = ft_atoi(&lem->input[i]);
	if (init_links(room) == 0)
		return (NULL);
	if (start_or_end == 1)
		lem->start = room;
	if (start_or_end == 2)
		lem->end = room;
	room->next = NULL;
	room->linked_rooms = NULL;
	room->level = 0;
	room->visited = 0;
	lem->i = i + ft_intlen(room->y) + 1;
	return (room);
}

int		save_room(t_lem *lem, int i, int j, int start_or_end)
{
	t_room			*room;
	t_room			*prev;
	char			*name;
	unsigned int	slot;

	name = ft_strcdup(&lem->input[i], ' ');
	slot = hash(name, lem->room_amount);
	room = lem->rooms[slot];
	if (room == NULL)
	{
		lem->rooms[slot] = get_room_info(lem, name, i, start_or_end);
		lem->j = j + 1;
		return (lem->i);
	}
	while (room != NULL)
	{
		if (ft_strcmp(room->c_name, name) == 0)
		{
			lem->j = j;
			//ft_printf("Found a duplicate\n");
			return (skip_line(lem->input, i));
		}
		prev = room;
		room = prev->next;
	}
	prev->next = get_room_info(lem, name, i, start_or_end);
	lem->j = j + 1;
	return (lem->i);
}

/*
** save start and end rooms
*/

int		get_start_and_end(t_lem *lem)
{
	int		start;
	int		end;

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
	lem->rooms = init_table(lem);
	get_start_and_end(lem);
	i = ft_intlen(lem->ants) + 1;
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
