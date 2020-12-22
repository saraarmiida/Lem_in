/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_links.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spentti <spentti@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:19:12 by spentti           #+#    #+#             */
/*   Updated: 2020/12/22 12:09:44 by spentti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

static t_rlink	*add_room_to_rooms_linked_rooms(t_room *room, t_room *room2)
{
	t_rlink *link;

	if (!(link = (t_rlink*)malloc(sizeof(t_rlink))))
		ft_error(strerror(errno));
	link->tgtroom = room2;
	link->next = NULL;
	if (room->linked_rooms)
		link->next = room->linked_rooms;
	room->linked_rooms = link;
	link->flow = 0;
	link->opp = NULL;
	return (link);
}

static int		check_link(t_lem *lem, int i)
{
	while (ft_isprint(lem->input[i]) && lem->input[i] != '-')
		i++;
	if (lem->input[i] != '-')
		return (0);
	i++;
	while (ft_isprint(lem->input[i]))
		i++;
	if (lem->input[i] != '\n')
		return (0);
	return (1);
}

static int		save_link(t_lem *lem, int i)
{
	t_room	*room1;
	t_room	*room2;
	t_rlink	*link1;
	t_rlink	*link2;
	char	*room_name;

	room_name = ft_strcdup(&lem->input[i], '-');
	i += ft_strlen(room_name) + 1;
	room1 = get_hashed_room(lem, room_name);
	room_name = ft_strcdup(&lem->input[i], '\n');
	i += ft_strlen(room_name) + 1;
	room2 = get_hashed_room(lem, room_name);
	if (room1 == NULL || room2 == NULL)
		return (-1);
	link1 = add_room_to_rooms_linked_rooms(room1, room2);
	link2 = add_room_to_rooms_linked_rooms(room2, room1);
	link1->opp = link2;
	link2->opp = link1;
	lem->link_nb++;
	if (lem->info == 1)
		print_edge_visu(link2, 'e');
	return (i);
}

int				get_links(t_lem *lem)
{
	int i;

	i = lem->i;
	if (lem->info == 1)
		ft_printf("#Rooms: %d\n", lem->room_nb);
	while (i != -1 && lem->input[i])
	{
		if (lem->input[i] == '#')
			i = skip_line(lem->input, i);
		else if ((check_link(lem, i) == 1))
			i = save_link(lem, i);
		else
			i = -1;
	}
	if (lem->link_nb == 0)
		ft_error("no links");
	if (lem->info == 1)
		ft_printf("#Links: %d\n", lem->link_nb);
	return (0);
}
