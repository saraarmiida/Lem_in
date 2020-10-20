#include "../includes/lem_in.h"

/*
** We try all child rooms of the current room until we find an unvisited room
** to be the next room of the path. (Should maybe add that room level should
** be always higher than the current rooms level)
** If we don't find an unvisited room, return NULL.
*/

t_path		*find_next_room(t_path *current, int visu_info)
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
			if (visu_info == 1)
				ft_printf("Curr: %d | %d | %d | %d\n", current->room->x, current->room->y, linked_rooms->room->x, linked_rooms->room->y);
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

t_path		*find_path(t_lem *lem)
{
	t_path	*current;
	t_path	*newroom;
	t_path	*head;

	head = init_new_path(lem);
	current = head;
	while (current->room != lem->end)
	{
		newroom = find_next_room(current, lem->visu_info);
		if (newroom == NULL)
		{
			if (current->prev != NULL)
				current = current->prev;
			if (current->room == lem->start) // where big.txt segfaults
				return (NULL);
		}
		else
		{
			current = newroom;
			lem->path_length++;
		}
	}
	return (head);
}

/*
** Creates a bucket of paths. Tries to create a new path, if there are
** unvisited rooms that connect to start room. Makes a linked list of
** paths that are found.
*/

int			create_bucket(t_lem *lem)
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
				return (0);
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
