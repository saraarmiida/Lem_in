#include "../includes/lem_in.h"

/*
** Backtracts path found from end room to start room, setting
** the flow of the edges to either 1 or 0, depending on if we
** used unused edge or edge with negative flow.
*/

void	mark_flow(t_queue *queue, t_lem *lem)
{
	ft_printf("\nMARKING FLOW\n");
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
		ft_printf("	edge %s flow %d|%d\n", queue->room->c_name, queue->edge->flow, queue->edge->opposite->flow);
		queue = queue->parent;
	}
	ft_printf("\n");
	lem->max_flow++;
}

void	remove_old_flow(t_room *room, t_room *start)
{
	t_rlink	*link;

	while (room != start)
	{
		link = room->linked_rooms;
		while (link != NULL && link->flow != -1)
			link = link->next;
		if (link->flow == -1)
		{
			link->flow = 0;
			link->opposite->flow = 0;
		}
		room = link->tgtroom;
	}
}

t_queue	*find_childq(t_queue *parentq, t_queue *childq, t_lem *lem)
{
	t_queue	*newq;
	t_rlink	*child;
	int		flow;
	static t_room	*crossing_old_path;

	newq = NULL;
	if (!crossing_old_path)
		crossing_old_path = NULL;
	flow = 0;
	child = parentq->room->linked_rooms;
	if (parentq->room->in_path == 1 && parentq->parent->room->in_path == 0)
		flow = 0;
	else
		flow = 1;
	ft_printf("\nFINDING CHILDQ\n");
	ft_printf("	parent: %s level %d\n", parentq->room->c_name, parentq->room->level);
	while (child != NULL)
	{
		if (child->tgtroom->visited == 0 && child->flow != 1 && child->flow != flow)
		{
			ft_printf("		1child: %s level %d visited %d flow %d\n", child->tgtroom->c_name, child->tgtroom->level, child->tgtroom->visited, child->flow);
			child->tgtroom->visited = 1;
			if (child->flow == 0)
				child->tgtroom->level = parentq->room->level + 1;
			else if (child->flow == -1)
				child->tgtroom->level = parentq->room->level - 1;
			newq = init_newq(child->tgtroom, child, parentq, lem);
			if (childq)
				newq->next = childq;
			childq = newq;
			if (child->tgtroom == lem->end)
			{
				mark_flow(childq, lem);
				return (childq);
			}
		}
		else if (child->tgtroom->visited == 0 && child->flow == 1 && (child->tgtroom->level > (parentq->room->level + 1) || child->tgtroom == lem->end))
		{
			if (crossing_old_path == NULL)
				crossing_old_path = child->tgtroom;
			ft_printf("		2child: %s level %d visited %d flow %d\n", child->tgtroom->c_name, child->tgtroom->level, child->tgtroom->visited, child->flow);
			child->tgtroom->visited = 1;
			child->tgtroom->level = parentq->room->level + 1;
			newq = init_newq(child->tgtroom, child, parentq, lem);
			if (childq)
				newq->next = childq;
			childq = newq;
			if (child->tgtroom == lem->end)
			{
				remove_old_flow(crossing_old_path, lem->start);
				lem->max_flow--;
				mark_flow(childq, lem);
				return (childq);
			}
		}
		else
		{
			ft_printf("		rejected child: %s level %d visited %d flow %d\n", child->tgtroom->c_name, child->tgtroom->level, child->tgtroom->visited, child->flow);
		}
		
		child = child->next;
	}
	return (childq);
}

/*
** We go through rooms with bfs, finding the shortest path that
** we haven't found yet. Instead of saving the path, we just mark
** the flow, which allows the use of negative flow, which can
** lead to finding more optimal paths.
*/

int		edmondskarp(t_lem *lem)
{
	t_queue			*parentq;
	t_queue			*childq;
	int				level;

	level = 0;
	childq = NULL;
	parentq = NULL;
	parentq = init_newq(lem->start, NULL, NULL, lem);
	lem->start->visited = 1;
	while (parentq != NULL)
	{
		while (parentq != NULL)
		{
			childq = find_childq(parentq, childq, lem);
			if (childq && childq->room == lem->end)
				return (1);
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
