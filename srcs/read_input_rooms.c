#include "../includes/lem_in.h"

static t_room	*get_room_info(t_lem *lem, char *name, int i)
{
	t_room	*room;

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		ft_error(strerror(errno));
	if (i == lem->start_i)
		lem->start = room;
	if (i == lem->end_i)
		lem->end = room;
	room->name = name;
	i += ft_strlen(room->name) + 1;
	room->x = ft_atoi(&lem->input[i]);
	i += ft_intlen(room->x) + 1;
	room->y = ft_atoi(&lem->input[i]);
	room->visited = 0;
	room->in_path = 0;
	room->next = NULL;
	room->linked_rooms = NULL;
	room->level = 0;
	room->ant = 0;
	if (lem->info == 1)
		ft_printf("#n|x%d|y%d|v%d|l%d|%s|c1|\n", room->x, room->y, room->visited, room->level, room->name);
	lem->i = i + ft_intlen(room->y) + 1;
	return (room);
}

static int		save_room(t_lem *lem, int i)
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
			if (ft_strcmp(room->name, name) == 0)
				ft_error("duplicate room");
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

static int		get_start_and_end(t_lem *lem)
{
	lem->start_i = ft_strmatchlen(lem->input, "##start\n");
	lem->end_i = ft_strmatchlen(lem->input, "##end\n");
	if (lem->start_i == -1 || lem->end_i == -1)
		ft_error("no start or end room");
	return (1);
}

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

int				get_rooms(t_lem *lem)
{
	int	i;

	check_rooms(lem);
	i = lem->i;
	lem->tablesize = lem->room_nb * 1.5;
	lem->rooms = init_table(lem);
	lem->j = 0;
	get_start_and_end(lem);
	while (lem->j < lem->room_nb)
	{
		if (lem->input[i] == '#')
			i = skip_line(lem->input, i);
		else
			i = save_room(lem, i);
	}
	lem->i = i;
	return (0);
}
