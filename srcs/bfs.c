#include "../includes/lem_in.h"

/*
** Problem: if temp is a copy of a pointer to linked_rooms, it already has all
** other rooms of linked_rooms connected to it -> how do we copy the whole linked list
** and not just the pointer to the first link?
** or do we just initially save the pointer to the first room in linked rooms and move the
** pointer of temp to the next one when we have iterated over the first one?
*/

// int		iterate_nodes(t_lem *lem, t_room *current)
// {
// 	t_rlink			*current_child;
// 	t_rlink			*temp;
// 	t_rlink			*prev;
// 	t_queues		*currentq;
// 	t_queues		*tempq;
// 	static int		level;
// 	static t_queues *temp_prevq;

// 	if (!level)
// 		level = 1;
// 	current_child = current->linked_rooms;
// 	if (!(currentq = (t_queues*)malloc(sizeof(t_queues))))
// 	{
// 		ft_printf("Could not allocate queue.");
// 		return (0);
// 	}
// 	currentq->nextq = NULL;
// 	currentq->prevq = NULL;
// 	currentq->prevq = temp_prevq;
// 	temp = current->linked_rooms;
// 	currentq->linked_rooms = temp;
// 	//ft_printf("Queue %s\n", currentq->linked_rooms->room->c_name);
// 	while (current_child)
// 	{
// 		if (current_child->room->level == 0 && lem->start != current_child->room)
// 		{
// 			current_child->room->level = current->level + 1;
// 			ft_printf("Saved room %s | ", current_child->room->c_name);
// 		}
// 		if (current_child->next)
// 			current_child = current_child->next;
// 		else
// 			current_child = NULL;
// 	}
// 	if (level > 1) {
// 		prev = currentq->linked_rooms;
// 		temp = currentq->linked_rooms->next;
// 		prev = NULL;
// 	}
// 	prev = NULL;
// 	if (temp->next == NULL)
// 	{
// 		//current = current_child->room->linked_rooms->room; // At this point current_child no longer exists -> segfault
// 		current = currentq->prevq->linked_rooms->room;
// 		level--;
// 		//ft_printf("temp->next was null.\n");
// 	}
// 	else
// 	{
// 		current = temp->next->room;
// 	}
// 	//ft_printf("Changed to next lvl.\n");
// 	if (current == lem->end)
// 		return(1);
// 	level++;
// 	tempq = currentq;
// 	currentq = currentq->nextq;
// 	temp_prevq = tempq;
// 	if (current != lem->end)
// 		level_rooms(lem, current);
// 	return(0);
// }

int		level_rooms(t_lem *lem, t_room *current)
{
	t_rlink			*current_child;
	t_queues		*newq;
	static int		level;
	static t_queues *temp_prevq;
	static t_queues	*currentq;

	if (!level)
		level = 1;
	current_child = current->linked_rooms;
	if (!(newq = (t_queues*)malloc(sizeof(t_queues))))
	{
		ft_printf("Could not allocate queue.");
		return (0);
	}
	newq->nextq = NULL;
	newq->prevq = NULL;
	newq->prevq = temp_prevq;
	newq->linked_rooms = current->linked_rooms;
	if (temp_prevq)
		temp_prevq->nextq = newq;
	//ft_printf("Queue %s\n", newq->linked_rooms->room->c_name);
	while (current_child)
	{
		if (current_child->room->level == 0 && lem->start != current_child->room)
		{
			current_child->room->level = current->level + 1;
			ft_printf("Saved room %s | ", current_child->room->c_name);
		}
		if (current_child->next)
			current_child = current_child->next;
		else
			current_child = NULL;
	}
	if (level == 1 || currentq->linked_rooms->next == NULL)
	{
		if (level == 1)
			currentq = newq;
		else if (currentq->nextq != NULL)
			currentq = currentq->nextq;
		else
			return (1);
	}
	else
	{
		currentq->linked_rooms = currentq->linked_rooms->next;
	}
	current = currentq->linked_rooms->room;
	level++;
	temp_prevq = newq;
	if (current != lem->end)
		level_rooms(lem, current);
	return(1);
}

/* Recursive function, on each function call, we create a path from start to end,
** we call the function again, if there still is a possibility to start a new path
** from start room (there is an unvisited room in start->linked rooms).
** To decide to which room to go next, we try to find an unvisited room with a higher
** level than the current room has. If can't continue the path, we traverse back until
** we can continue (and mark traversed rooms unvisited)
** We save the path to a bucket of paths if it leads to end room.
** - Do we need to delete dead ends at this point?
** 
*/

int		find_paths(t_lem *lem)
{
	t_path	*head;
	t_path	*current;
	t_rlink	*saved_linked_rooms;

	if (!(head = (t_path*)malloc(sizeof(t_path))))
	{
		ft_printf("Malloc failed");
		return(0);
	}
	head->room = lem->start;
	head->prev = NULL;
	head->next = NULL;
	current = head;
	while (current->room != lem->end)
	{
		saved_linked_rooms = current->room->linked_rooms;
		while (current->room->linked_rooms)
		{
			if (current->room->linked_rooms->room->level > current->room->level)
			{
				if (!(current->next = (t_path*)malloc(sizeof(t_path))))
				{
					ft_printf("Malloc failed");
					return(0);
				}
				current->room->linked_rooms = saved_linked_rooms;
				current->next->prev = current;
				current->next->room = current->room->linked_rooms->room;
				current->next->next = NULL;
				break ;
			}
			else
			{
				current->room->linked_rooms = current->room->linked_rooms->next;
			}
		}
		current = current->next;
	}
	current = head;
	ft_printf("Path:\n");
	while (current)
	{
		ft_printf("%s -> ", current->room->c_name);
		current = current->next;
	}
	return (0);
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
	if (level_rooms(lem, lem->start) == 1)
		ft_printf("Rooms leveled.\n");
	else
		ft_printf("BFS did not complete.\n\nDebug info:\n");
	print_debug_info(lem);
	// if (find_paths(lem) == 1)
	// 	ft_printf("Paths found.\n");
	// else
	// 	ft_printf("BFS did not complete.\n\nDebug info:\n");
}
