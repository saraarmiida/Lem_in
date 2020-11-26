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
	path->ants = 0;
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

static int	find_path(t_lem *lem, t_bucket *set)
{
	t_rlink	*current;
	t_path	*node;
	t_path	*head;
	int		len;

	current = lem->start->linked_rooms;
	node = init_node(lem->start, NULL, lem);
	head = node;
	len = 0;
	while (current != NULL)
	{
		if (current->flow == 1 && current->tgtroom->visited == 0)
		{
			len++;
			node = init_node(current->tgtroom, node, lem);
			if (current->tgtroom == lem->end)
				return (save_path(head, len, set));
			current->tgtroom->level = len;
			current = current->tgtroom->linked_rooms;
		}
		else
			current = current->next;
	}
	free_path(head);
	return (0);
}

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
		find_path(lem, set);
	set->cost = ((set->length + lem->ants) / set->flow) - 1;
	if (lem->best_set == NULL || set->cost < lem->best_set->cost)
	{
		if (lem->best_set)
			free_set(lem->best_set);
		lem->best_set = set;
	}
	else
		free_set(set);
	// print_path(lem->best_set);
}

/*
** solve first goes through rooms, marking flows while searching for paths.
** On the second iteration we already know how many paths are possible to find
** (max_flow) and we search paths based on how we marked the flows.
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
