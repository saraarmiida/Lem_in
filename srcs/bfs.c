#include "../includes/lem_in.h"

/*
** Goes through all rooms, giving all of them levels based on how far they
** are from the start room. We go through all of the child rooms of a room
** (parameter current) and give them one higher level than the parent room has.
** We also save the child rooms as a queue to newq, so that later we can
** check all of their child rooms, until we reach the end room. We save the
** queues in a queue, and always first check if there still are child rooms
** left in our current queue, if not we go to the next queue if there is one.
*/

/*
int			level_rooms2(t_lem *lem, t_room *current, t_rlink *edge)
{
	t_rlink	*templink;

	templink = NULL;
	while (current->linked_rooms != NULL && current->linked_rooms->flow == 0)
	{
		ft_printf("Edgge from %d to %d used. Switching to %d to %d.\n", current->name, current->linked_rooms->tgtroom->name, current->name, current->linked_rooms->next->tgtroom->name);
		current->linked_rooms = current->linked_rooms->next;
	}
	if (current->linked_rooms == NULL) // Would this ever happen
	{
		ft_printf("Ruum %d did not have edges.\n", current->name);
		return (0);
	}
	if (edge == NULL)
		edge = current->linked_rooms;
	while (edge != NULL && edge->flow == 1)
	{
		ft_printf("Leveling at %d. ", current->name);
		if (edge->tgtroom->level == 0 && edge->tgtroom != lem->start)
		{
			ft_printf("Leveling room %d: %d.\n", edge->tgtroom->name, current->level + 1);
			edge->tgtroom->level = current->level + 1;
		}
		edge = current->linked_rooms->next;
	}
	templink = current->linked_rooms;
	while (lem->start != current && templink->tgtroom->level >= current->level)
		templink = templink->next;
	current = templink->tgtroom;
	if (current != lem->end)
		level_rooms2(lem, templink->tgtroom, edge);
	return (1);	
}
*/

int			level_rooms(t_lem *lem, t_room *current, t_queues *temp_prevq)
{
	t_rlink			*edge;
	t_queues		*newq;
	static t_queues	*currentq;

	ft_printf("CURRENT IS %d.\n", current->name);
	edge = NULL;
	if (current->linked_rooms ==  NULL)
	{
		ft_printf("Ruum has no edges. Returning 0.\n");
		return (0);
	}
	if (current->visited == 1)
	{
		current->visited = 0;
		edge = current->linked_rooms;
		while (edge->flow == 0)
			edge = edge->next;
		newq = init_newq(temp_prevq, current);
		ft_printf("Et: %d | Ef: %d\n", edge->tgtroom->name, edge->flow);
		while (edge != NULL && edge->flow == 1)
		{
			if (lem->lvl_flow == 1 && edge->flow == 0)
			{
				ft_printf("Egde to %d is at max. Tgt level is at %d.\n", edge->tgtroom->name, edge->tgtroom->level);
				edge = current->linked_rooms;
			}
			else if (edge->tgtroom->level == 0 && lem->start != edge->tgtroom && edge->flow == 1)
			{
				ft_printf("		Leveling room %d: %d.\n", edge->tgtroom->name, current->level + 1);
				edge->tgtroom->level = current->level + 1;
				if (current->linked_rooms->next->flow == 1)
				{
					ft_printf("Egde now from %d: %d.\n", current->name, current->linked_rooms->next->tgtroom->name);
					edge = current->linked_rooms->next;
				}
				else	
					edge = NULL;
			}
			else
			{
				ft_printf("Tried room %d. Fail. \n", current->name, edge->tgtroom->name);
				edge = edge->next;
			}
		}
	}
	else
		newq = temp_prevq;
	if (!currentq)
		currentq = newq;
	else if (currentq->linked_rooms->next != NULL && currentq->linked_rooms->next->flow == 1)
		currentq->linked_rooms = currentq->linked_rooms->next; // This links 1 to the queue even with the if above
	else if (currentq->nextq != NULL)
		currentq = currentq->nextq;
	else
		return (0);
	current = currentq->linked_rooms->tgtroom;

	if (current != lem->end)
		level_rooms(lem, current, newq);
	currentq =  NULL;
	return (1);
}

void		bfs(t_lem *lem)
{
	if (lem->start)
		ft_printf("\nWe have a start\n");
	while (level_rooms(lem, lem->start, NULL) == 1)
	{
		lem->lvl_flow = 1;
		ft_printf("Ruums leveled.\n");
		if (create_bucket(lem) == 1)
			ft_printf("\nPaths maybe found.\n\n\n");
		else
			ft_printf("Buckets not complete.\n\nDebug info:\n");
	}
	if (lem->visu_info == 0)
		print_debug_info(lem);
}
