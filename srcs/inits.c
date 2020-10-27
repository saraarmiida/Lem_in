#include "../includes/lem_in.h"

/*
** Initializes a new queue, linking the possible previous queue to
** it and adding the children rooms of the current parent room to the queue
*/

t_queues	*init_newq(t_queues *temp_prevq, t_room *current)
{
	t_queues	*newq;
	t_rlink		*templink;

	if (!(newq = (t_queues*)malloc(sizeof(t_queues))))
	{
		ft_printf("Could not allocate queue.");
		return (0);
	}
	newq->nextq = NULL;
	newq->prevq = temp_prevq;
	templink = current->linked_rooms;
	while (templink->flow == 0)
		templink = templink->next;
	newq->linked_rooms = templink;
	if (temp_prevq)
		temp_prevq->nextq = newq;
	return (newq);
}

t_path		*init_new_path(t_lem *lem)
{
	t_path *head;

	if (!(head = (t_path*)malloc(sizeof(t_path))))
	{
		ft_printf("Malloc failed");
		return (NULL);
	}
	head->room = lem->start;
	head->prev = NULL;
	head->next = NULL;
	lem->path_length = 0;
	return (head);
}

void		*init_table(t_lem *lem)
{
	int			i;
	t_room		**rooms;

	rooms = (t_room**)malloc(sizeof(t_room) * (lem->tablesize));
	i = 0;
	while (i < lem->tablesize)
	{
		rooms[i] = NULL;
		i++;
	}
	return (rooms);
}

void		init_lem(t_lem *lem)
{
	lem->fd = 3;
	lem->ants = 0;
	lem->room_amount = 0;
	lem->link_amount = 0;
	lem->path_length = 0;
	lem->tablesize = 0;
	lem->input = NULL;
	lem->j = 0;
	lem->i = 0;
	lem->info = 0;
	lem->bucketlist = NULL;
	lem->lvl_flow = 0;
}
