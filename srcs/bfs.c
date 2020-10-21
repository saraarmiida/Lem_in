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

int			level_rooms(t_lem *lem, t_room *current, t_queues *temp_prevq)
{
	t_rlink			*child;
	t_queues		*newq;
	static t_queues	*currentq;

	if (current->visited == 1)
	{
		current->visited = 0;
		child = current->linked_rooms;
		newq = init_newq(temp_prevq, current);
		while (child)
		{
			if (lem->lvl_flow == 1 && child->visited == 1)
				child = child->next;
			if (child->room->level == 0 && lem->start != child->room)
			{
				child->room->level = current->level + 1;
			}
			child = child->next;
		}
	}
	else
		newq = temp_prevq;
	if (!currentq)
		currentq = newq;
	else if (currentq->linked_rooms->next != NULL)
		currentq->linked_rooms = currentq->linked_rooms->next;
	else if (currentq->nextq != NULL)
		currentq = currentq->nextq;
	else
		return (1);
	current = currentq->linked_rooms->room;
	if (current != lem->end)
		level_rooms(lem, current, newq);
	return (1);
}

void		bfs(t_lem *lem)
{
	if (lem->start)
		ft_printf("\nWe have a start\n");
	if (level_rooms(lem, lem->start, NULL) == 1)
	{
		lem->lvl_flow = 1;
		ft_printf("Rooms leveled.\n");
	}
	else
	{
		ft_printf("BFS did not complete.\n\nDebug info:\n");
		if (lem->visu_info == 0)
			print_debug_info(lem);
	}
	if (create_bucket(lem) == 1)
		ft_printf("\nPaths found.\n\n\n");
	else
		ft_printf("BFS did not complete.\n\nDebug info:\n");
}
