#include "../includes/lem_in.h"

/*
** We try all child rooms of the current room until we find an unvisited room
** to be the next room of the path. (Should maybe add that room level should
** be always higher than the current rooms level)
** If we don't find an unvisited room, return NULL.
*/


static void reset_edges(t_lem *lem, t_rlink *edge1, t_rlink *edge2)
{
	t_room	*r;
	t_rlink	*templink;
	int		i;

	i = 0;
	templink = NULL;
	while (i < lem->tablesize)
	{
		r = lem->rooms[i];
		if (r != NULL)
		{
			templink = r->linked_rooms;
			while (templink != NULL && templink != edge1 && templink != edge2)
			{
				templink->flow = 1;
				templink = templink->next;
			}
			while (r->next != NULL)
			{
				r = r->next;
				templink = r->linked_rooms;
				while (templink != NULL && templink != edge1 && templink != edge2)
				{
					templink->flow = 1;
					templink = templink->next;
				}
			}
		}
		i++;
	}
}

static void reset_levels_and_visited(t_lem *lem)
{
	t_room	*r;
	int		i;

	i = 0;
	while (i < lem->tablesize)
	{
		r = lem->rooms[i];
		if (r != NULL)
		{
			r->level = 0;
			r->visited = 1; 
			while (r->next != NULL)
			{
				r = r->next;
				r->level = 0; 
				r->visited = 1;
			}
		}
		i++;
	}
	lem->end->visited = 0;
}

static void	update_edges_and_reset(t_path *path, t_lem *lem)
{
	t_rlink	*usededge;
	t_rlink *tempedge;
	t_rlink *edge1;
	t_rlink *edge2;

	edge1 = NULL;
	edge2 = NULL;
	tempedge = NULL;
	while (path->next != NULL)
	{
		usededge = path->room->linked_rooms;
		while (usededge->tgtroom != path->next->room)
			usededge = usededge->next;
		usededge->flow = 0;
		tempedge = usededge->tgtroom->linked_rooms;
		while (tempedge != NULL)
		{
			if (tempedge->tgtroom == path->room && tempedge->flow == 0)
			{
				//ft_printf("\n\nPATH USED BOTH WAYS!!\n\n");
				edge1 = usededge;
				edge2 = tempedge;
			}
			tempedge = tempedge->next;
		}
		path = path->next;
	}
	if (edge1 != NULL)
		reset_edges(lem, edge1, edge2);
	reset_levels_and_visited(lem);
}

t_path		*find_next_room(t_path *current, int info)
{
	t_rlink	*edge;

	edge = current->room->linked_rooms;
	while (edge != NULL)
	{
		if (edge->tgtroom->level > current->room->level && edge->flow == 1 && edge->tgtroom->visited == 0)
		{
			edge->tgtroom->visited = 1;
			if (!(current->next = (t_path*)malloc(sizeof(t_path))))
			{
				ft_printf("Malloc failed");
				return (NULL);
			}
			if (info == 1)
				ft_printf("|-\t-|Curr: %d | %d | %d | %d | Nimi: %d\n", current->room->x, current->room->y, edge->tgtroom->x, edge->tgtroom->y, current->room->name);
			current->next->prev = current;
			current->next->room = edge->tgtroom;
			current->next->next = NULL;
			return (current->next);
		}
		edge = edge->next;
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
		newroom = find_next_room(current, lem->info);
		if (newroom == NULL)
		{
			if (current->prev != NULL)
			{
				current = current->prev;
			}
			if (current->room == lem->start)
				return (NULL);
		}
		else
		{	
			current = newroom;
			lem->path_length++; // Not accurate. Includes the failed paths to the sum
		}
	}
	return (head);
}

/*
** Creates a bucket of paths. Tries to create a new path, if there are
** unvisited rooms that connect to start room. Makes a linked list of
** paths that are found.
*/

t_path		*add_path_to_bucket(t_lem *lem, t_bucket *bucket)
{
	t_path		*head;
	t_paths		*temp_paths;

	if (!bucket)
		return (NULL);
	head = find_path(lem);
	if (head != NULL)
	{
		if (bucket->paths == NULL)
		{
			if (!(temp_paths = (t_paths*)malloc(sizeof(t_paths))))
			{
				ft_printf("Malloc failed");
				return (NULL);
			}
			temp_paths->path = NULL;
			temp_paths->path = head;
			temp_paths->next_path = NULL;
			temp_paths->length = 0;
			bucket->paths = temp_paths;
		}
		else
		{
			temp_paths = bucket->paths;
			while (temp_paths->next_path != NULL)
				temp_paths = temp_paths->next_path;
			if (!(temp_paths->next_path = (t_paths*)malloc(sizeof(t_paths))))
			{
				ft_printf("Bucket malloc failed");
				return (0);
			}
			temp_paths = temp_paths->next_path;
			temp_paths->path = NULL;
			temp_paths->path = head;
			temp_paths->next_path = NULL;
			temp_paths->length = 0;
		}
		//temp_paths->length += lem->path_length;
		update_edges_and_reset(head, lem);
	}
	ft_printf("Path %p returned. Length is %d\n", head, lem->path_length);
	return (head);
}