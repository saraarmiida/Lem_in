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
				//ft_printf("		Updated edge from %d to %d to 1.\n", r->name, templink->tgtroom->name);
				templink->flow = 1;
				templink = templink->next;
			}
			while (r->next != NULL)
			{
				r = r->next;
				templink = r->linked_rooms;
				while (templink != NULL && templink != edge1 && templink != edge2)
				{
					//ft_printf("		Updated edge from %d to %d to 1.\n", lem->rooms[i]->name, templink->tgtroom->name);
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
			//ft_printf("Leveled room %d to 0.\n", lem->rooms[i]->name);
			while (r->next != NULL)
			{
				r = r->next;
				r->level = 0; 
				r->visited = 1;
				//ft_printf("Leveled room %d to 0.\n", lem->rooms[i]->name);
			}
		}
		i++;
	}
	lem->start->visited = 1;
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
		//ft_printf("Updated egde from %d to %d. Now %d.\n", path->room->name, usededge->tgtroom->name, usededge->flow);
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
	//ft_printf("Finding next room. Right now at %d, checking if %d is ok. Visited there: %d\n", current->room->name, edge->tgtroom->name, edge->tgtroom->visited);
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
			//ft_printf("Backing down to: %d\n", current->room->name);
			if (current->room == lem->start)
				return (NULL);
		}
		else
		{	
			//ft_printf("Moved from %d to %d.\n", current->room->name, newroom->room->name);
			current = newroom;
			lem->path_length++;
		}
	}
	//ft_printf("Returning a path starting at: %d\n", head->room->name);
	return (head);
}

/*
** Creates a bucket of paths. Tries to create a new path, if there are
** unvisited rooms that connect to start room. Makes a linked list of
** paths that are found.
*/

int			create_bucket(t_lem *lem)
{
	t_paths		*bucket;
	t_paths		*temp_bucket;
	t_path		*temp_path;
	t_path		*path;
	t_rlink		*start_room;

	temp_bucket = NULL;
	temp_path = NULL;
	start_room = lem->start->linked_rooms;
	if (!(bucket = (t_paths*)malloc(sizeof(t_paths))))
	{
		ft_printf("Malloc failed");
		return (0);
	}
	bucket->paths = NULL;
	if (lem->paths == NULL)
		lem->paths = bucket;
	else
	{
		temp_bucket = lem->paths;
		while(temp_bucket->next_set != NULL)
			temp_bucket = temp_bucket->next_set;
		temp_bucket->next_set = bucket;
	}
	while (start_room != NULL)
	{
		path = find_path(lem);
		if (path != NULL)
		{
			print_onepath(path);
			if (bucket->paths ==  NULL)
			{
				if (!(bucket->paths = (t_paths*)malloc(sizeof(t_paths))))
				{
					ft_printf("Malloc failed");
					return (0);
				}
				bucket->paths->path = NULL;
				bucket->paths->next_path = NULL;
				bucket->paths->next_set = NULL;
			}
			if (bucket->paths->path == NULL)
				bucket->paths->path = path;
			else
			{
				while (bucket->paths->next_path != NULL)
				{
					//ft_printf("Looping much? ");
					//ft_printf("What's inside: %d", bucket->paths->next_path->length);
					bucket->paths->path = bucket->paths->next_path;
				}
				bucket->paths->next_path = path;
			}
			bucket->total_length += lem->path_length; // Change to count
			bucket->next_path = NULL;
			update_edges_and_reset(path, lem);
		}
		bucket->next_set = NULL;
		start_room = start_room->next;
	}
	return (1);
}
