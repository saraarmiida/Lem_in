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
						return (find_path(childq, lem->start, level + 1));
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
	path = NULL;
	i = 0;
	while (i < 3)
	{
		path = edmondskarp(lem);
		if (path != NULL)
		{
			save_path(lem, path);
			reset_rooms(lem);
			print_path(lem->paths);
		}
		i++;
	}
	return (0);
}
