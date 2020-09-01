#include "../includes/lem_in.h"

int		iterate_nodes(t_lem *lem, t_room *current)
{
	t_rlink		*current_child;
	t_rlink		*temp;
	t_rlink		*prev;
	t_queues	*queues;
	static int	level;

	if (!level)
		level = 1;
	current_child = current->linked_rooms;
	if (!(queues = (t_queues*)malloc(sizeof(t_queues))))
	{
		ft_printf("Could not allocate queue.");
		return (0);
	}
	queues->next = NULL;
	if (!(temp = (t_rlink*)malloc(sizeof(t_rlink))))
	{
		ft_printf("Could not allocate temp.");
		return (0);
	}
	ft_memcpy(temp, current_child, sizeof(t_rlink));
	queues->linked_rooms = temp;
	ft_printf("Queue %s\n", queues->linked_rooms->room->c_name);
	while (current_child)
	{
		if (current_child->room->level == 0 && lem->start != current_child->room)
		{
			current_child->room->level = level;
			if (!(temp = (t_rlink*)malloc(sizeof(t_rlink))))
			{
				ft_printf("Could not allocate temp.");
				return (0);
			}
			ft_printf("Saved room %s | ", current_child->room->c_name);
			if (current_child->next)
			{
				if (!(temp->next = (t_rlink*)malloc(sizeof(t_rlink))))
				{
					ft_printf("Could not allocate temp->next.");
					return (0);
				}
				ft_memcpy(temp->next, current_child->next, sizeof(t_rlink));
				temp = temp->next;
				current_child = current_child->next;
			}
			else {
				current_child = NULL;
				temp->next = NULL;
			}
		}
		else
		{
			if (current_child->next)
				current_child = current_child->next;
			else
				current_child = NULL;
		}
	}
	if (level > 1) {
		prev = temp;
		temp = temp->next;
		prev = NULL;
	}
	if (current->linked_rooms->next == NULL)
		current = current_child->room->linked_rooms->room;
	else
		current = current->linked_rooms->room;
	ft_printf("Changed to next lvl.\n");
	level++;
	queues = queues->next;
	if (current == lem->end)
		return(1);
	else
		iterate_nodes(lem, current);
	return(0);
}

void	bfs(t_lem *lem)
{
	if (!(lem->routes = (t_route**)malloc(sizeof(t_route) * lem->room_amount / 2)))
	{
		ft_printf("Malloc failed");
		return ;
	}
	if (lem->start)
		ft_printf("We have a start");
	if (iterate_nodes(lem, lem->start) == 1)
		ft_printf("Nodes iterated");
}