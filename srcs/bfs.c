#include "../includes/lem_in.h"

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
	path->next = NULL;
	path->length = length;
	return (path);
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
	parentq = init_newq(lem->start, NULL, NULL);
	lem->start->visited = 1;
	end = 0;
	while (end == 0 && parentq != NULL)
	{
		while (parentq != NULL && end == 0)
		{
			child = parentq->room->linked_rooms;
			while (child != NULL && end == 0)
			{
				if (child->flow == 1 && child->tgtroom->visited == 0)
				{
					// ft_printf("parent: %s child: %s level %d\n", parentq->room->c_name, child->tgtroom->c_name, level);
					child->tgtroom->visited = 1;
					child->tgtroom->level = parentq->room->level + 1;
					newq = init_newq(child->tgtroom, child, parentq);
					if (childq)
						newq->next = childq;
					childq = newq;
					if (child->tgtroom == lem->end)
					{
						end = 1;
						return (find_path(childq, lem->start, level + 1));
					}
				}
				child = child->next;
			}
			parentq = parentq->next;
		}
		level++;
		parentq = childq;
		childq = NULL;
	}
	return (NULL);
}

void	save_flow(t_queue *queue, t_room *start)
{
	while (queue->room != start)
	{
		if (queue->edge->flow == 0)
		{
			queue->edge->flow = 1;
			queue->edge->opposite->flow = -1;
		}
		else if (queue->edge->flow == -1)
		{
			queue->edge->flow = 0;
			queue->edge->opposite->flow = 0;
		}
		queue = queue->parent;
	}
}

int		edmondskarp_flow(t_lem *lem)
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
	parentq = init_newq(lem->start, NULL, NULL);
	lem->start->visited = 1;
	end = 0;
	while (end == 0 && parentq != NULL)
	{
		while (parentq != NULL && end == 0)
		{
			child = parentq->room->linked_rooms;
			while (child != NULL && end == 0)
			{
				if (child->tgtroom->visited == 0 && child->flow != 1)
				{
					// ft_printf("parent: %s child: %s level %d\n", parentq->room->c_name, child->tgtroom->c_name, level);
					child->tgtroom->visited = 1;
					child->tgtroom->level = parentq->room->level + 1;
					newq = init_newq(child->tgtroom, child, parentq);
					if (childq)
						newq->next = childq;
					childq = newq;
					if (child->tgtroom == lem->end)
					{
						end = 1;
						save_flow(childq, lem->start);
						return (1);
					}
				}
				child = child->next;
			}
			parentq = parentq->next;
		}
		level++;
		parentq = childq;
		childq = NULL;
	}
	return (0);
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

void	save_path(t_lem *lem, t_paths *path)
{
	if (lem->paths == NULL)
		lem->paths = path;
	else
	{
		path->next = lem->paths;
		lem->paths = path;
	}
}

int		solve(t_lem *lem)
{
	t_paths	*path;
	t_rlink	*start_room;
	int		i;

	start_room = lem->start->linked_rooms;
	i = 0;
	while (start_room != NULL && i <= lem->ants)
	{
		if (edmondskarp_flow(lem) == 1)
		{
			reset_rooms(lem);
			// print_path(lem->paths);
		}
		start_room = start_room->next;
		i++;
	}
	start_room = lem->start->linked_rooms;
	path = NULL;
	i = 0;
	while (start_room != NULL && i <= lem->ants)
	{
		path = edmondskarp(lem);
		if (path != NULL)
		{
			save_path(lem, path);
			reset_rooms(lem);
			print_path(lem->paths);
		}
		start_room = start_room->next;
		i++;
	}
	return (0);
}
