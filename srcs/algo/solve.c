/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraarmiida <saraarmiida@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:09:26 by saraarmiida       #+#    #+#             */
/*   Updated: 2020/12/14 13:09:29 by saraarmiida      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Saves found path to struct
*/

static int	save_path(t_path *head, int length, t_bucket *set)
{
	t_paths	*path;

	if (!(path = (t_paths*)malloc(sizeof(t_paths))))
		ft_error(strerror(errno));
	path->path = head;
	path->next = NULL;
	path->length = length;
	if (set->paths == NULL)
		set->paths = path;
	else
	{
		path->next = set->paths;
		set->paths = path;
	}
	set->length += length;
	return (1);
}

/*
** Finds a path from start to end, can only use flows of 1.
*/

static int	find_path(t_lem *lem, t_bucket *set, int len)
{
	t_rlink	*current;
	t_path	*node;
	t_path	*head;

	current = lem->start->linked_rooms;
	node = init_node(lem->start, NULL, lem, 0);
	head = node;
	while (current != NULL)
	{
		if (current->flow == 1 && current->tgtroom->visited == 0)
		{
			len++;
			node = init_node(current->tgtroom, node, lem, len);
			if (current->tgtroom == lem->end)
				return (save_path(head, len, set));
			if (lem->info == 1)
				print_room_visu(current->tgtroom);
			current = current->tgtroom->linked_rooms;
		}
		else
			current = current->next;
	}
	free_path(head);
	return (0);
}

/*
** Finds all possible paths and saves them in a set. Counts how
** many lines would it take to send the ants through the new set
** and replaces current best set if the new one is better.
*/

static void	find_set(t_lem *lem)
{
	int			j;
	t_bucket	*set;

	if (!(set = (t_bucket*)malloc(sizeof(t_bucket))))
		ft_error(strerror(errno));
	set->paths = NULL;
	set->length = 0;
	set->flow = lem->max_flow;
	j = -1;
	while (++j < lem->max_flow)
		find_path(lem, set, 0);
	set->cost = ((set->length + lem->ants) / set->flow) - 1;
	if (set->length == 1)
		set->cost = 1;
	if (lem->best_set == NULL || set->cost < lem->best_set->cost)
	{
		if (lem->best_set)
			free_set(lem->best_set);
		lem->best_set = set;
	}
	else
		free_set(set);
	if (lem->info == 1)
		print_path(lem->best_set);
}

/*
** solve has a loop which continues as long as there is possibility to find
** a new path. In the loop, edmondskarp finds and marks the flow and find_set
** creates a new set of paths with the flow that has been found until now.
*/

int			solve(t_lem *lem)
{
	int	x;

	x = 1;
	while (x == 1)
	{
		x = edmondskarp(lem);
		if (lem->last_queue)
			free_queue(lem->last_queue);
		lem->last_queue = NULL;
		if (x == 0)
			break ;
		reset_rooms(lem);
		find_set(lem);
		reset_rooms(lem);
	}
	if (lem->best_set == NULL)
		ft_error("no possible path");
	return (0);
}
