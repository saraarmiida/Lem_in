#include "../includes/lem_in.h"

t_queues	*init_newq(t_queues *temp_prevq, t_room *current)
{
	t_queues	*newq;

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
	return (newq);
}

int		level_rooms(t_lem *lem, t_room *current)
{
	t_rlink			*current_child;
	t_queues		*newq;
	static int		level;
	static t_queues *temp_prevq;
	static t_queues	*currentq;

	level = !level ? 1 : level;
	current_child = current->linked_rooms;
	if (!temp_prevq)
		temp_prevq = NULL;
	newq = init_newq(temp_prevq, current);
	while (current_child)
	{
		if (current_child->room->level == 0 && lem->start != current_child->room)
			current_child->room->level = current->level + 1;
		if (current_child->next)
		{
			//if (lem->visu_info == 1)
			//	ft_printf("Curr: %d | %d | %d | %d\n", current->x, current->y, current_child->room->x, current_child->room->y);
			current_child = current_child->next;
		}
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
		currentq->linked_rooms = currentq->linked_rooms->next;
	current = currentq->linked_rooms->room;
	level++;
	temp_prevq = newq;
	if (current != lem->end)
		level_rooms(lem, current);
	return(1);
}

/* 
**Recursive function, on each function call, we create a path from start to end,
** we call the function again, if there still is a possibility to start a new path
** from start room (there is an unvisited room in start->linked rooms).
** To decide to which room to go next, we try to find an unvisited room with a higher
** level than the current room has. If can't continue the path, we traverse back until
** we can continue (and mark traversed rooms unvisited)
** We save the path to a bucket of paths if it leads to end room.
*/

t_path	*find_next_room(t_path *current)
{
	t_rlink	*saved_linked_rooms;
	
	current->room->visited = 1;
	saved_linked_rooms = current->room->linked_rooms;
	while (current->room->linked_rooms)
	{
		if (current->room->linked_rooms->room->visited == 0)
		{
			if (!(current->next = (t_path*)malloc(sizeof(t_path))))
			{
				ft_printf("Malloc failed");
				return (NULL);
			}
			ft_printf("Curr: %d | %d | %d | %d\n", current->room->x, current->room->y, current->room->linked_rooms->room->x, current->room->linked_rooms->room->y);
			current->next->prev = current;
			current->next->room = current->room->linked_rooms->room;
			current->next->next = NULL;
			current->room->linked_rooms = saved_linked_rooms;
			break ;
		}
		else
		{
			if (current->room->linked_rooms->next != NULL)
				current->room->linked_rooms = current->room->linked_rooms->next;
			else
				current = find_next_room(current->prev);
		}
	}
	return (current->next);
}

/*
** Creates a single path. Makes a linked list of rooms that lead
** from start to end room. Returns NULL if path couldn't be found.
*/

t_path	*find_path(t_room *path_start, t_room *start, t_room *end)
{
	t_path	*current;
	t_path	*head;

	if (!(head = (t_path*)malloc(sizeof(t_path))))
	{
		ft_printf("Malloc failed");
		return(0);
	}
	head->room = path_start;
	head->prev = NULL;
	head->next = NULL;
	current = head;
	while (current->room != end && current->room != start)
		current = find_next_room(current);
	if (current->room == start)
		return (NULL);
	return (head);
}

/*
** Creates a bucket of paths. Tries to create a new path, if there are
** unvisited rooms that connect to start room. Makes a linked list of
** paths that are found.
*/

int		create_bucket(t_lem *lem)
{
	t_paths			*bucket;
	t_paths			*temp_prev_path;
	t_path			*path;
	t_rlink			*start_room;

	temp_prev_path = NULL;
	start_room = lem->start->linked_rooms;
	while (start_room != NULL)
	{
		if (start_room->room->visited == 0)
		{
			path = find_path(start_room->room, lem->start, lem->end);
			if (path != NULL)
			{
				if (!(bucket = (t_paths*)malloc(sizeof(t_paths))))
				{
					ft_printf("Malloc failed");
					return(0);
				}
				bucket->path = path;
				bucket->next = NULL;
				if (temp_prev_path)
					temp_prev_path->next = bucket;
				temp_prev_path = bucket;
				if (!lem->paths)
					lem->paths = bucket;
			}
		}
		start_room = start_room->next;
	}

	return (1);
}

void	bfs(t_lem *lem)
{
	if (lem->start)
		ft_printf("We have a start\n");
	if (level_rooms(lem, lem->start) == 1)
		ft_printf("Rooms leveled.\n");
	else
		ft_printf("BFS did not complete.\n\nDebug info:\n");
	if (create_bucket(lem) == 1)
		ft_printf("\nPaths found.\n\n\n");
	else
		ft_printf("BFS did not complete.\n\nDebug info:\n");
}
