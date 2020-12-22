/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spentti <spentti@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:19:36 by spentti           #+#    #+#             */
/*   Updated: 2020/12/22 12:09:59 by spentti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

t_path		**init_ants(int ants)
{
	t_path	**ant;
	int		i;

	i = 0;
	if (!(ant = (t_path**)malloc(sizeof(t_path*) * ants)))
		ft_error(strerror(errno));
	while (i < ants)
	{
		ant[i] = NULL;
		i++;
	}
	return (ant);
}

t_path		*init_node(t_room *room, t_path *prev, t_lem *lem, int len)
{
	t_path	*node;

	if (!(node = (t_path*)malloc(sizeof(t_path))))
		ft_error(strerror(errno));
	node->room = room;
	node->next = NULL;
	node->prev = prev;
	if (prev != NULL)
		prev->next = node;
	if (room != lem->start && room != lem->end)
	{
		room->visited = 1;
		room->in_path = 1;
		room->level = len;
	}
	return (node);
}

t_queue		*init_newq(t_room *room, t_rlink *edge, t_queue *parent, t_lem *lem)
{
	t_queue			*newq;
	static t_queue	*prev;

	if (!prev)
		prev = NULL;
	if (!(newq = (t_queue*)malloc(sizeof(t_queue))))
		ft_error(strerror(errno));
	newq->room = room;
	newq->edge = edge;
	newq->parent = parent;
	newq->next = NULL;
	newq->prev = prev;
	lem->last_queue = newq;
	if (room != lem->end)
		prev = newq;
	else
		prev = NULL;
	return (newq);
}

void		*init_table(t_lem *lem)
{
	int			i;
	t_room		**rooms;

	if (!(rooms = (t_room**)malloc(sizeof(t_room) * (lem->tablesize))))
		ft_error(strerror(errno));
	i = 0;
	while (i < lem->tablesize)
	{
		rooms[i] = NULL;
		i++;
	}
	return (rooms);
}

void		init_lem(t_lem *lem)
{
	lem->best_set = NULL;
	lem->input = NULL;
	lem->start_i = 0;
	lem->end_i = 0;
	lem->max_flow = 0;
	lem->path_length = 0;
	lem->ants = 0;
	lem->room_nb = 0;
	lem->tablesize = 0;
	lem->link_nb = 0;
	lem->i = 0;
	lem->j = 0;
	lem->info = 0;
	lem->print_lines = 0;
	lem->print_set = 0;
	lem->quiet = 0;
	lem->required = 0;
	lem->leaks = 0;
}
