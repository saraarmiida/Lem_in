#include "../includes/lem_in.h"

/*
** Initializes a new queue, linking the possible previous queue to
** it and adding the children rooms of the current parent room to the queue
*/

t_queues	*init_newq(t_queues *temp_prevq, t_room *current)
{
	t_queues	*newq;

	if (!(newq = (t_queues*)malloc(sizeof(t_queues))))
	{
		ft_printf("Could not allocate queue.");
		return (0);
	}
	newq->nextq = NULL;
	newq->prevq = temp_prevq;
	newq->linked_rooms = current->linked_rooms;
	if (temp_prevq)
		temp_prevq->nextq = newq;
	return (newq);
}

/*
** Goes through all rooms, giving all of them levels based on how far they
** are from the start room. We go through all of the child rooms of a room
** (parameter current) and give them one higher level than the parent room has.
** We also save the child rooms as a queue to newq, so that later we can
** check all of their child rooms, until we reach the end room. We save the queues
** in a queue, and always first check if there still are child rooms left in our
** current queue, if not we go to the next queue if there is one.
*/

int		level_rooms(t_lem *lem, t_room *current)
{
	t_rlink			*current_child;
	t_queues		*newq;
	static int		level;
	static t_queues *temp_prevq;
	static t_queues	*currentq;

	if (!level)
		level = 1;
	if (!temp_prevq)
		temp_prevq = NULL;
	current_child = current->linked_rooms;
	newq = init_newq(temp_prevq, current);
	while (current_child)
	{
		if (current_child->room->level == 0 && lem->start != current_child->room)
			current_child->room->level = current->level + 1;
		// ft_printf("Curr: %d | %d | %d | %d\n", current->x, current->y, current_child->room->x, current_child->room->y);
		current_child = current_child->next;
	}
	if (level == 1)
		currentq = newq;
	else if (currentq->linked_rooms->next != NULL)
		currentq->linked_rooms = currentq->linked_rooms->next;
	else if (currentq->nextq != NULL)
		currentq = currentq->nextq;
	else
		return (1);
	current = currentq->linked_rooms->room;
	level++;
	temp_prevq = newq;
	if (current != lem->end)
		level_rooms(lem, current);
	return(1);
}

/*
** We try all child rooms of the current room until we find an unvisited room
** to be the next room of the path. (Should maybe add that room level should
** be always higher than the current rooms level)
** If we don't find an unvisited room, we try to find another route from the previous room.
*/

t_path	*find_next_room(t_path *current)
{
	t_rlink	*linked_rooms;
	
	current->room->visited = 1;
	linked_rooms = current->room->linked_rooms;
	while (linked_rooms != NULL)
	{
		if (linked_rooms->room->visited == 0)
		{
			if (!(current->next = (t_path*)malloc(sizeof(t_path))))
			{
				ft_printf("Malloc failed");
				return (NULL);
			}
			// ft_printf("Curr: %d | %d | %d | %d\n", current->room->x, current->room->y, linked_rooms->room->x, linked_rooms->room->y);
			current->next->prev = current;
			current->next->room = linked_rooms->room;
			current->next->next = NULL;
			return (current->next);
		}
		linked_rooms = linked_rooms->next;
	}
	return (NULL);
}

/*
** Creates a single path. Makes a linked list of rooms that lead
** from start to end room. Returns NULL if path couldn't be found.
*/

t_path	*find_path(t_lem *lem)
{
	t_path	*current;
	t_path	*newroom;
	t_path	*head;
	int		length;

	if (!(head = (t_path*)malloc(sizeof(t_path))))
	{
		ft_printf("Malloc failed");
		return(0);
	}
	head->room = lem->start;
	head->prev = NULL;
	head->next = NULL;
	current = head;
	length = 0;
	while (current->room != lem->end)
	{
		newroom = find_next_room(current);
		if (newroom == NULL)
		{
			current = current->prev;
			if (current->room == lem->start)
				return (NULL);
		}
		else
		{
			current = newroom;
			length++;
		}
	}
	lem->path_length = length;
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
		path = find_path(lem);
		if (path != NULL)
		{
			if (!(bucket = (t_paths*)malloc(sizeof(t_paths))))
			{
				ft_printf("Malloc failed");
				return(0);
			}
			bucket->path = path;
			bucket->length = lem->path_length;
			bucket->next = NULL;
			if (temp_prev_path)
				temp_prev_path->next = bucket;
			temp_prev_path = bucket;
			if (!lem->paths)
				lem->paths = bucket;
		}
		start_room = start_room->next;
	}
	return (1);
}

void	bfs(t_lem *lem)
{
	if (lem->visu_info == 1)
		ft_printf("Rooms: %d Links: %d", lem->room_amount, lem->link_amount);
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
