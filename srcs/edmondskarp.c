#include "../includes/lem_in.h"

/*
** Backtracts path found from end room to start room, setting
** the flow of the edges to either 1 or 0, depending on if we
** used unused edge or edge with negative flow.
*/

static void		mark_flow(t_queue *queue, t_lem *lem)
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
		if (lem->info == 1)
			ft_printf("#s|fx%d|fy%d|tx%d|ty%d|f%d\n", queue->edge->opposite->tgtroom->x, queue->edge->opposite->tgtroom->y, queue->edge->tgtroom->x, queue->edge->tgtroom->y, queue->edge->flow);
		queue = queue->parent;
	}
	lem->max_flow++;
}

static t_queue	*save_newq(t_rlink *child, t_queue *pq, t_queue *cq, t_lem *l)
{
	t_queue	*newq;

	newq = NULL;
	if (child->flow == -1)
		child->tgtroom->level = pq->room->level - 1;
	else
		child->tgtroom->level = pq->room->level + 1;
	child->tgtroom->visited = 1;
	if (l->info == 1)
		ft_printf("#n|x%d|y%d|v%d|l%d|%s|c1|\n", child->tgtroom->x, child->tgtroom->y, child->tgtroom->visited, child->tgtroom->level, child->tgtroom->name);
	newq = init_newq(child->tgtroom, child, pq, l);
	if (cq)
		newq->next = cq;
	cq = newq;
	if (child->tgtroom == l->end)
	{
		mark_flow(cq, l);
		return (cq);
	}
	return (cq);
}

static t_queue	*find_childq(t_queue *parentq, t_queue *childq, t_lem *lem)
{
	t_rlink			*child;
	static t_room	*crossing_old_path;
	int				flow;

	if (!crossing_old_path)
		crossing_old_path = NULL;
	child = parentq->room->linked_rooms;
	flow = 1;
	if (parentq->room->in_path == 1 && parentq->parent->room->in_path == 0)
		flow = 0;
	while (child != NULL)
	{
		if (child->tgtroom->visited == 0 && child->flow != 1 \
		&& child->flow != flow)
		{
			childq = save_newq(child, parentq, childq, lem);
			if (childq && childq->room == lem->end)
				return (childq);
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

int				edmondskarp(t_lem *lem)
{
	t_queue			*parentq;
	t_queue			*childq;

	childq = NULL;
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
		parentq = childq;
		childq = NULL;
	}
	if (lem->max_flow == 0)
		ft_error("no possible path");
	return (0);
}
