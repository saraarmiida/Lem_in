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

t_room	*get_room_info(t_lem *lem, char *name, int i)
{
	t_room	*room;

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		ft_error("malloc error");
	if (i == lem->start_i)
		lem->start = room;
	if (i == lem->end_i)
		lem->end = room;
	room->c_name = name;
	i += ft_strlen(room->c_name) + 1;
	room->x = ft_atoi(&lem->input[i]);
	i += ft_intlen(room->x) + 1;
	room->y = ft_atoi(&lem->input[i]);
	room->visited = 0;
	room->next = NULL;
	room->linked_rooms = NULL;
	room->level = 0;
	room->ant = 0;
	lem->i = i + ft_intlen(room->y) + 1;
	return (room);
}

int		save_room(t_lem *lem, int i)
{
	t_room			*room;
	t_room			*prev;
	char			*name;
	unsigned int	slot;

	name = ft_strcdup(&lem->input[i], ' ');
	slot = hash(name, lem->tablesize);
	room = lem->rooms[slot];
	if (room == NULL)
	{
		lem->rooms[slot] = get_room_info(lem, name, i);
		lem->j += 1;
		return (lem->i);
	}
	else
	{
		while (room != NULL)
		{
			if (ft_strcmp(room->c_name, name) == 0)
			{
				ft_error("duplicate room");
			}
			prev = room;
			room = prev->next;
		}
		prev->next = get_room_info(lem, name, i);
		lem->j += 1;
	}
	return (lem->i);
}

/*
** save start and end rooms
*/

int		get_start_and_end(t_lem *lem)
{
	lem->start_i = ft_strmatchlen(lem->input, "##start\n");
	lem->end_i = ft_strmatchlen(lem->input, "##end\n");
	if (lem->start_i == -1 || lem->end_i == -1)
		ft_error("no start or end room");
	return (1);
}

/*
** validates room syntax
*/

int		check_room(t_lem *lem, int i)
{
	int j;

	j = i;
	if (lem->input[i] == 'L' || lem->input[i] == '#')
		ft_error("invalid room name");
	while (lem->input[j] != '\n' && lem->input[j])
	{
		if (lem->input[j] == '-' && !(ft_isdigit(lem->input[j + 1]) == 1 && lem->input[j - 1] == ' '))
			return (-1);
		j++;
	}
	while (ft_isprint(lem->input[i]) && lem->input[i] != ' ')
		i++;
	if (lem->input[i] != ' ')
		return (-2);
	i++;
	if (lem->input[i] == '-')
		i++;
	while (ft_isdigit(lem->input[i]))
		i++;
	if (lem->input[i] != ' ')
		return (-2);
	i++;
	if (lem->input[i] == '-')
		i++;
	while (ft_isdigit(lem->input[i]))
		i++;
	if (lem->input[i] != '\n')
		return (-2);
	lem->room_amount++;
	return (i + 1);
}

int		get_rooms(t_lem *lem)
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
	lem->tablesize = lem->room_amount * 1.5;
	lem->rooms = init_table(lem);
	lem->j = 0;
	get_start_and_end(lem);
	i = ft_intlen(lem->ants) + 1;
	while (lem->j < lem->room_amount)
	{
		if (lem->input[i] == '#')
			i = skip_line(lem->input, i);
		else
			i = save_room(lem, i);
	}
	lem->i = i;
	return (0);
}
