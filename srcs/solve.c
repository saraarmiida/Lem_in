#include "../includes/lem_in.h"

/*
** Sets all rooms to be unvisited.
*/

void	reset_rooms(t_lem *lem)
{
	int		i;
	t_room	*r;

	i = 0;
	while (i < lem->tablesize)
	{
		r = lem->rooms[i];
		if (r != NULL)
		{
			if (r->visited == 1)
				r->visited = 0;
			while (r->next != NULL)
			{
				r = r->next;
				if (r->visited == 1)
					r->visited = 0;
			}
		}
		i++;
	}
	lem->start->visited = 0;
	lem->end->visited = 0;
}

/*
** Saves found path to struct
*/

int	save_path(t_path *head, int length, t_bucket *set)
{
	t_paths	*path;

	if (!(path = (t_paths*)malloc(sizeof(t_paths))))
		return (0);
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

int		find_path(t_lem *lem, t_bucket *set)
{
	t_rlink	*current;
	t_path	*node;
	t_path	*newnode;
	t_path	*head;
	int		len;

	current = lem->start->linked_rooms;
	node = init_node(lem->start, NULL);
	head = node;
	len = 0;
	while (current != NULL)
	{
		if (current->flow == 1 && current->tgtroom->visited == 0)
		{
			len++;
			newnode = init_node(current->tgtroom, node);
			node->next = newnode;
			if (current->tgtroom == lem->end)
				return (save_path(head, len, set));
			node = newnode;
			current->tgtroom->visited = 1;
			current = current->tgtroom->linked_rooms;
		}
		else
			current = current->next;
	}
	return (0);
}

/*
** Backtracts path found from end room to start room, setting the flow of the edges
** to either 1 or 0, depending on if we used unused edge or edge with negative flow.
*/

void	mark_flow(t_queue *queue, t_lem *lem)
{
	while (queue->room != lem->start)
	{
		if (queue->edge->flow == 0)
		{
			queue->edge->flow = 1;
			queue->edge->opposite->flow = -1;
		}
		else if (queue->edge->flow == -1)
		{
			queue->edge->flow = 0;
			queue->edge->opposite->flow = 0;
		}
		queue = queue->parent;
	}
	lem->max_flow++;
}

/*
** We go through rooms with bfs, finding the shortest path that we haven't found yet.
** Instead of saving the path, we just mark the flow, which allows the use of negative
** flow, which can lead to finding more optimal paths.
*/

int		edmondskarp(t_lem *lem)
{
	t_queue			*parentq;
	t_rlink			*child;
	t_queue			*childq;
	int				level;
	t_queue			*newq;

	level = 0;
	childq = NULL;
	parentq = NULL;
	child = NULL;
	newq = NULL;
	parentq = init_newq(lem->start, NULL, NULL);
	lem->start->visited = 1;
	while (parentq != NULL)
	{
		while (parentq != NULL)
		{
			child = parentq->room->linked_rooms;
			while (child != NULL)
			{
				if (child->tgtroom->visited == 0 && child->flow != 1)
				{
					// ft_printf("parent: %s child: %s level %d\n", parentq->room->c_name, child->tgtroom->c_name, level);
					child->tgtroom->visited = 1;
					child->tgtroom->level = parentq->room->level + 1;
					newq = init_newq(child->tgtroom, child, parentq);
					if (childq)
						newq->next = childq;
					childq = newq;
					if (child->tgtroom == lem->end)
					{
						mark_flow(childq, lem);
						return (1);
					}
				}
				child = child->next;
			}
			parentq = parentq->next;
		}
		level++;
		parentq = childq;
		childq = NULL;
	}
	if (lem->max_flow == 0)
		ft_error("no possible path");
	return (0);
}

int		calc_cost(t_bucket *set, int ants)
{
	set->cost = ((set->length + ants) / set->flow) - 1;
	return (set->cost);
}

void	find_set(t_lem *lem)
{
	int			j;
	t_bucket	*set;
	int			cost;

	if (!(set = (t_bucket*)malloc(sizeof(t_bucket))))
		return ;
	set->paths = NULL;
	set->length = 0;
	set->flow = lem->max_flow;
	set->cost = 0;
	j = 0;
	while (j < lem->max_flow)
	{
		find_path(lem, set);
		j++;
	}
	cost = calc_cost(set, lem->ants);
	if (lem->best_set == NULL || cost < lem->best_set->cost)
		lem->best_set = set;
	print_path(lem->best_set);
}

/*
** solve first goes through rooms, marking flows while searching for paths.
** On the second iteration we already know how many paths are possible to find
** (max_flow) and we search paths based on how we marked the flows.
*/

int		solve(t_lem *lem)
{
	t_rlink	*start_room;
	int		i;

	start_room = lem->start->linked_rooms;
	i = 0;
	while (start_room != NULL && i <= lem->ants)
	{
		edmondskarp(lem);
		reset_rooms(lem);
		find_set(lem);
		reset_rooms(lem);
		start_room = start_room->next;
		i++;
	}
	if (lem->best_set == NULL)
		ft_error("no possible path");
	return (0);
}
