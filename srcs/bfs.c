#include "../includes/lem_in.h"

/*
** Problem: if temp is a copy of a pointer to linked_rooms, it already has all
** other rooms of linked_rooms connected to it -> how do we copy the whole linked list
** and not just the pointer to the first link?
** or do we just initially save the pointer to the first room in linked rooms and move the
** pointer of temp to the next one when we have iterated over the first one?
*/

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
	temp = current->linked_rooms;
	queues->linked_rooms = temp;
	ft_printf("Queue %s\n", queues->linked_rooms->room->c_name);
	while (current_child)
	{
		if (current_child->room->level == 0 && lem->start != current_child->room)
		{
			current_child->room->level = level;
			ft_printf("Saved room %s | ", current_child->room->c_name);
			if (current_child->next)
			{
				current_child = current_child->next;
			}
			else {
				current_child = NULL;
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
		prev = queues->linked_rooms;
		temp = queues->linked_rooms->next;
		prev = NULL;
	}
	if (temp->next == NULL)
		current = current_child->room->linked_rooms->room;
	else
		current = temp->next->room;
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
		ft_printf("We have a start\n");
	if (iterate_nodes(lem, lem->start) == 1)
		ft_printf("Nodes iterated\n");
}