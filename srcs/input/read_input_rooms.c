/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_rooms.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraarmiida <saraarmiida@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:10:05 by saraarmiida       #+#    #+#             */
/*   Updated: 2020/12/14 13:10:06 by saraarmiida      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		print_room_visu(room);
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
		lem->rooms[slot] = get_room_info(lem, name, i);
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
	}
	lem->j += 1;
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
