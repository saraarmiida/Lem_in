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

// t_bucket	*init_bucket(t_lem *lem)
// {
// 	t_bucket *bucket;

// 	bucket =  NULL;
// 	if (lem->bucketlist == NULL)
// 	{
// 		if (!(bucket = (t_bucket*)malloc(sizeof(t_bucket))))
// 		{
// 			ft_printf("Bucket malloc failed");
// 			return (0);
// 		}
// 		bucket->path = NULL;
// 		bucket->paths = NULL;
// 		bucket->next_bucket = NULL;
// 		bucket->length = 0;
// 		lem->bucketlist = bucket;
// 	}
// 	else
// 	{
// 		bucket = lem->bucketlist;
// 		while (bucket->next_bucket != NULL)
// 			bucket = bucket->next_bucket;
// 		if (!(bucket->next_bucket = (t_bucket*)malloc(sizeof(t_bucket))))
// 		{
// 			ft_printf("Bucket malloc failed");
// 			return (0);
// 		}
// 		bucket = bucket->next_bucket;
// 		bucket->path = NULL;
// 		bucket->paths = NULL;
// 		bucket->next_bucket = NULL;
// 		bucket->length = 0;
// 	}
// 	return (bucket);
// }

// int		create_bucket(t_lem *lem)
// {
// 	t_bucket	*bucket;
// 	t_rlink		*start_room;
// 	int			i;

// 	i = 0;
// 	bucket = init_bucket(lem);
// 	start_room = lem->start->linked_rooms;
// 	while (start_room != NULL)
// 	{
// 		if (level_rooms(lem, lem->start, NULL) == 1)
// 		{
// 			ft_printf("rooms leveled\n");
// 			ft_printf("\nstart_room is %s\n", start_room->tgtroom->c_name);
// 			while ((add_path_to_bucket(lem, bucket)) == NULL)
// 				ft_printf("Added null path to bucket %p. Bucket length is now %d\n", bucket, bucket->length);
// 			ft_printf("Added path to bucket %p. Bucket length is now %d\n", bucket, bucket->length);
// 		}
// 		else
// 			return (0);
// 		start_room = start_room->next;
// 	}
// 	return (1);
// }

t_path		*init_node(t_room *room, t_path *next)
{
	t_path	*node;

	if (!(node = (t_path*)malloc(sizeof(t_path))))
		return (0);
	node->room = room;
	node->next = next;
	node->prev = NULL;
	node->room->visited = 2;
	return (node);
}

t_paths		*find_path(t_queue *queue, t_room *start, int length)
{
	t_paths	*path;
	t_path	*node;
	t_path	*newnode;

	node = init_node(queue->room, NULL);
	while (node->room != start)
	{
		queue = queue->parent;
		newnode = init_node(queue->room, node);
		node->prev = newnode;
		node = newnode;

	}
	if (!(path = (t_paths*)malloc(sizeof(t_paths))))
		return (0);
	path->path = node;
	path->next_path = NULL;
	path->length = length;
	return (path);
}

void		print_queue(t_queue *queue, int l)
{
	t_queue	*q;

	q = queue;
	ft_printf("queue l %d: ", l);
	while (q != NULL)
	{
		ft_printf("| %s ", q->room->c_name);
		q = q->next;
	}
	ft_printf("\n");
}

t_paths		*edmondskarp(t_lem *lem)
{
	t_queue			*parentq;
	t_rlink			*child;
	t_queue			*childq;
	int				level;
	int				end;
	t_queue			*newq;

	level = 0;
	childq = NULL;
	parentq = NULL;
	child = NULL;
	newq = NULL;
	parentq = init_newq(lem->start, NULL);
	lem->start->visited = 1;
	end = 0;
	while (end == 0 && parentq != NULL)
	{
		while (parentq != NULL && end == 0)
		{
			child = parentq->room->linked_rooms;
			while (child != NULL && end == 0)
			{
				if (child->tgtroom->visited == 0)
				{
					// ft_printf("parent: %s child: %s level %d\n", parentq->room->c_name, child->tgtroom->c_name, level);
					child->tgtroom->visited = 1;
					child->tgtroom->level = parentq->room->level + 1;
					newq = init_newq(child->tgtroom, parentq);
					if (childq)
						newq->next = childq;
					childq = newq;
					if (child->tgtroom == lem->end)
					{
						end = 1;
						return (find_path(childq, lem->start, level));
					}
				}
				child = child->next;
			}
			// if (parentq->next != NULL)
			// 	ft_printf("	parent change %s -> %s\n\n", parentq->room->c_name, parentq->next->room->c_name);
			parentq = parentq->next;
		}
		level++;
		// if (childq != NULL)
		// {
		// 	print_queue(childq, level - 1);
		// 	ft_printf("	next level parent changes to -> %s\n\n", childq->room->c_name);
		// }
		parentq = childq;
		childq = NULL;
	}
	return (NULL);
}

void		print_path(t_paths *paths)
{
	t_paths		*temp_paths;
	t_path		*temp_path;
	int			i;

	i = 1;
	temp_paths = paths;
	ft_printf("\nPRINTING PATHS\n");
	while (temp_paths != NULL)
	{
		temp_path = temp_paths->path;
		ft_printf("Path:\n");
		while (temp_path != NULL)
		{
			ft_printf("	Room %s (level: %d)\n", temp_path->room->c_name, temp_path->room->level);
			temp_path = temp_path->next;
		}
		temp_paths = temp_paths->next_path;
	}
}

void	reset_rooms(t_lem *lem)
{
	int		i;
	t_room	*r;

	i = 0;
	while (i < lem->tablesize)
	{
		r = lem->rooms[i];
		if (r != NULL)
		{
			if (r->visited == 1)
				r->visited = 0;
			while (r->next != NULL)
			{
				r = r->next;
				if (r->visited == 1)
					r->visited = 0;
			}
		}
		i++;
	}
	lem->start->visited = 0;
	lem->end->visited = 0;
}

int		solve(t_lem *lem)
{
	t_paths	*path;
	t_rlink	*start_room;
	int		i;

	start_room = lem->start->linked_rooms;
	path = NULL;
	i = 0;
	while (i < 3)
	{
		path = edmondskarp(lem);
		if (path != NULL)
		{
			reset_rooms(lem);
			print_path(path);
		}
		i++;
	}
	return (0);
}
