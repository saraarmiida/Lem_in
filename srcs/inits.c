#include "../includes/lem_in.h"

t_path		*init_node(t_room *room, t_path *prev, t_lem *lem)
{
	t_path	*node;

	if (!(node = (t_path*)malloc(sizeof(t_path))))
		return (NULL);
	node->room = room;
	node->next = NULL;
	node->prev = prev;
	if (prev != NULL)
		prev->next = node;
	if (room != lem->start && room != lem->end)
	{
		room->visited = 1;
		room->in_path = 1;
	}
	return (node);
}

t_queue		*init_newq(t_room *room, t_rlink *edge, t_queue *parent, t_lem *lem)
{
	t_queue			*newq;
	static t_queue	*prev;

	if (!prev)
		prev = NULL;
	if (!(newq = (t_queue*)malloc(sizeof(t_queue))))
	{
		ft_printf("Could not allocate queue.");
		return (0);
	}
	newq->room = room;
	newq->edge = edge;
	newq->parent = parent;
	newq->next = NULL;
	newq->prev = prev;
	lem->last_queue = newq;
	if (room != lem->end)
		prev = newq;
	else
		prev = NULL;
	return (newq);
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
	lem->best_set = NULL;
	lem->input = NULL;
	lem->start_i = 0;
	lem->end_i = 0;
	lem->max_flow = 0;
	lem->path_length = 0;
	lem->ants = 0;
	lem->room_amount = 0;
	lem->tablesize = 0;
	lem->link_amount = 0;
	lem->i = 0;
	lem->j = 0;
	lem->info = 0;
	lem->fd = 3; // can delete
}
