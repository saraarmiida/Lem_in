#include "../includes/lem_in.h"

/*
** Problem: if temp is a copy of a pointer to linked_rooms, it already has all
** other rooms of linked_rooms connected to it -> how do we copy the whole linked list
** and not just the pointer to the first link?
** or do we just initially save the pointer to the first room in linked rooms and move the
** pointer of temp to the next one when we have iterated over the first one?
*/

int		iterate_nodes(t_lem *lem, t_room *current)
{
	t_rlink			*current_child;
	t_rlink			*temp;
	t_rlink			*prev;
	t_queues		*currentq;
	t_queues		*tempq;
	static int		level;
	static t_queues *temp_prevq;

	if (!level)
		level = 1;
	current_child = current->linked_rooms;
	if (!(currentq = (t_queues*)malloc(sizeof(t_queues))))
	{
		ft_printf("Could not allocate queue.");
		return (0);
	}
	currentq->nextq = NULL;
	currentq->prevq = NULL;
	currentq->prevq = temp_prevq;
	temp = current->linked_rooms;
	currentq->linked_rooms = temp;
	//ft_printf("Queue %s\n", currentq->linked_rooms->room->c_name);
	while (current_child)
	{
		if (current_child->room->level == 0 && lem->start != current_child->room)
		{
			current_child->room->level = current->level + 1;
			ft_printf("Saved room %s | ", current_child->room->c_name);
			if (current_child->next)
			{
				current_child = current_child->next;
			}
			else {
				current_child = NULL;
			}
		}
		else
		{
			if (current_child->next)
				current_child = current_child->next;
			else
				current_child = NULL;
		}
	}
	if (level > 1) {
		prev = currentq->linked_rooms;
		temp = currentq->linked_rooms->next;
		prev = NULL;
	}
	if (temp->next == NULL)
	{
		//current = current_child->room->linked_rooms->room; // At this point current_child no longer exists -> segfault
		current = currentq->prevq->linked_rooms->room;
		level--;
		//ft_printf("temp->next was null.\n");
	}
	else
	{
		current = temp->next->room;
	}
	//ft_printf("Changed to next lvl.\n");
	if (lem->current == lem->end)
		return(1);
	level++;
	tempq = currentq;
	currentq = currentq->nextq;
	temp_prevq = tempq;
	if (current != lem->end)
		iterate_nodes(lem, current);
	return(0);
}

void	bfs(t_lem *lem)
{
	if (!(lem->routes = (t_route**)malloc(sizeof(t_route) * lem->room_amount / 2)))
	{
		ft_printf("Malloc failed");
		return ;
	}
	if (lem->start)
		ft_printf("We have a start\n");
	if (iterate_nodes(lem, lem->start) == 1)
		ft_printf("Nodes iterated.\n");
	else
		ft_printf("BFS did not complete.\n\nDebug info:\n");
}