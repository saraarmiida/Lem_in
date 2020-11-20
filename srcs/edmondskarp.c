#include "../includes/lem_in.h"

/*
** Backtracts path found from end room to start room, setting
** the flow of the edges to either 1 or 0, depending on if we
** used unused edge or edge with negative flow.
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
** We go through rooms with bfs, finding the shortest path that
** we haven't found yet. Instead of saving the path, we just mark
** the flow, which allows the use of negative flow, which can
** lead to finding more optimal paths.
*/

int		edmondskarp(t_lem *lem)
{
	t_queue			*parentq;
	t_queue			*childq;
	t_queue			*newq;
	t_rlink			*child;
	int				level;

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
