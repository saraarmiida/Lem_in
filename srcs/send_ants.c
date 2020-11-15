
#include "../includes/lem_in.h"

/*
** Sends a new ant to the shortest path, then evaluates whether it makes
** sense to send another ant to the next shortest path. It makes sense to
** send an ant to a path if path length is less than length of the shorter
** paths combined with the amount of ants left.
*/

int		send_new_ants(t_paths *path, int ant, t_lem *lem)
{
	int	length;

	length = 0;
	while (path != NULL && ant <= lem->ants)
	{
		ft_printf("L%d-%s ", ant, path->path->next->room->c_name);
		path->path->next->room->ant = ant;
		if (path->length > lem->path_length)
			lem->path_length = path->length;
		length = path->length;
		path = path->next;
		if (path != NULL && length + (lem->ants - ant) <= path->length)
			return (ant + 1);
		ant++;
	}
	return (ant);
}

/*
** Goes through all rooms in a path, and if there is an ant in a room, it
** moves the ant to the next room.
*/

void	move_ants(t_path *room, t_room *end)
{
	int	temp_ant;
	int	running_ant;

	running_ant = 0;
	while (room->room != end)
	{
		if (room->room->ant != 0)
		{
			ft_printf("L%d-%s ", room->room->ant, room->next->room->c_name);
		}
		temp_ant = room->room->ant;
		room->room->ant = running_ant;
		running_ant = room->next->room == end ? 0 : temp_ant;
		room = room->next;
	}
}


/*
** sorts paths from shortest to longest
*/


void	sort_paths(t_lem *lem)
{
	int		temp_length;
	t_path	*temp_path;
	t_paths	*current;
	t_paths	*next;

	current = lem->paths;
	while (current->next != NULL)
	{
		next = current->next;
		while (next != NULL)
		{
			if (current->length > next->length)
			{
				temp_length = current->length;
				temp_path = current->path;
				current->path = next->path;
				current->length = next->length;
				next->path = temp_path;
				next->length = temp_length;
			}
			next = next->next;
		}
		current = current->next;
	}
}

/*
** Keeps track of how many rounds are still needed to get the latest sent
** ant to end room (lem->path_length) and while it is > 0, we move all ants that
** are currently on paths and if there are still ants in the start room, we
** send new ants to paths.
*/


void	send_ants(t_lem *lem)
{
	int		ant;
	t_paths	*path;
	t_paths	*start;
	int		i;

	ft_printf("%s\n\n", lem->input); // add ignoring comments
	ant = 1;
	i = 0;
	sort_paths(lem);
	lem->path_length = lem->paths->length;
	start = lem->paths;
	while (lem->path_length > 0)
	{
		path = start;
		while (path != NULL)
		{
			move_ants(path->path->next, lem->end);
			path = path->next;
		}
		if (ant <= lem->ants)
		{
			ant = send_new_ants(start, ant, lem);
		}
		lem->path_length--;
		ft_printf("\n");
		i++;
	}
	ft_printf("lines %d\n", i);
}
