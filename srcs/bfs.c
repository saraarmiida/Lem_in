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
	t_rlink			*edge;
	t_queues		*newq;
	t_rlink			*temp;
	int				i;
	int				j;
	static t_queues	*currentq;

	//ft_printf("CURRENT IS %d.\n", current->name);
	edge = NULL;
	temp = NULL;
	i = 0;
	j = 0;
	if (current->linked_rooms ==  NULL)
	{
		//ft_printf("Ruum has no edges. Returning 0.\n");
		return (0);
	}
	if (current == lem->start)
	{
		temp = current->linked_rooms;
		while (temp != NULL)
		{
			if (temp->flow == 0)
				j++;
			i++;
			temp = temp->next;
		}
		if (i == j)
			return (0);
	}
	if (current->visited == 1)
	{
		current->visited = 0;
		edge = current->linked_rooms;
		while (edge->flow == 0)
			edge = edge->next;
		newq = init_newq(temp_prevq, current);
		//ft_printf("Et: %d | Ef: %d\n", edge->tgtroom->name, edge->flow);
		while (edge != NULL && edge->flow == 1)
		{
			if (lem->lvl_flow == 1 && edge->flow == 0)
			{
				//ft_printf("Egde to %d is at max. Tgt level is at %d.\n", edge->tgtroom->name, edge->tgtroom->level);
				edge = current->linked_rooms;
			}
			else if (edge->tgtroom->level == 0 && lem->start != edge->tgtroom && edge->flow == 1)
			{
				//ft_printf("		Leveling room %d: %d.\n", edge->tgtroom->name, current->level + 1);
				edge->tgtroom->level = current->level + 1;
				if (current->linked_rooms->next->flow == 1)
				{
					//ft_printf("Egde now from %d: %d.\n", current->name, current->linked_rooms->next->tgtroom->name);
					edge = current->linked_rooms->next;
				}
				else	
					edge = NULL;
			}
			else
			{
				//ft_printf("Tried room %d. Fail. \n", current->name, edge->tgtroom->name);
				edge = edge->next;
			}
		}
	}
	else
		newq = temp_prevq;
	if (!currentq)
		currentq = newq;
	else if (currentq->linked_rooms->next != NULL && currentq->linked_rooms->next->flow == 1)
		currentq->linked_rooms = currentq->linked_rooms->next;
	else if (currentq->nextq != NULL)
		currentq = currentq->nextq;
	else
		return (0);
	current = currentq->linked_rooms->tgtroom;
	if (current != lem->end)
		level_rooms(lem, current, newq);
	currentq =  NULL;
	lem->end->visited = 0;
	return (1);
}

int		create_bucket(t_lem *lem)
{
	t_bucket	*bucket;
	t_rlink		*start_room;
	int			i;

	i = 0;
	start_room = lem->start->linked_rooms;
	bucket =  NULL;
	if (lem->bucketlist == NULL)
	{
		if (!(bucket = (t_bucket*)malloc(sizeof(t_bucket))))
		{
			ft_printf("Bucket malloc failed");
			return (0);
		}
		bucket->path = NULL;
		bucket->next_path = NULL;
		bucket->next_bucket = NULL;
		bucket->length = 0;
		lem->bucketlist = bucket;
	}
	else
	{
		bucket = lem->bucketlist;
		while (bucket->next_bucket != NULL)
			bucket = bucket->next_bucket;
		if (!(bucket->next_bucket = (t_bucket*)malloc(sizeof(t_bucket))))
		{
			ft_printf("Bucket malloc failed");
			return (0);
		}
		bucket = bucket->next_bucket;
		bucket->path = NULL;
		bucket->next_path = NULL;
		bucket->next_bucket = NULL;
		bucket->length = 0;
	}
	if (level_rooms(lem, lem->start, NULL) == 1)
	{
		while (start_room != NULL)
		{
			ft_printf("\nstart_room is %d\n", start_room->tgtroom->name);
			if ((add_path_to_bucket(lem, bucket)) != NULL)
				ft_printf("Added path to bucket %p. Bucket length is now %d\n", bucket, bucket->length);
			else
				ft_printf("Added null path to bucket %p. Bucket length is now %d\n", bucket, bucket->length);
			start_room = start_room->next;
		}
	}
	else
		return (0);
	return (1);
}
