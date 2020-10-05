#include "../includes/lem_in.h"

/*
** send_new_ants sends a new ant to each path that makes sense to send an ant in.
** if paths length is less than other paths length + remaining ants, it makes sense
** to send an ant to that path.
*/

int		send_new_ants(t_paths *path, int ant, t_lem *lem)
{
	int	length;

	length = 0;
	while (path != NULL && ant < lem->ants)
	{
		ft_printf("L%d-%s ", ant, path->path->next->room->c_name);
		path->path->next->room->ant = ant;
		lem->path_length = path->length > lem->path_length ? path->length : lem->path_length;
		length += path->length;
		if (path->next != NULL && length + (lem->ants - ant) <= path->next->length)
			return (ant + 1);
		ant++;
		path = path->next;
	}
	return (ant);
}

void	move_ants(t_path *room, t_room *end)
{
	int			temp_ant;
	static int	running_ant;

	if (!running_ant)
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

void	send_ants(t_lem *lem)
{
	int		ant;
	t_paths	*path;
	t_paths	*start;

	ft_printf("%s\n\n", lem->input); // add ignoring comments
	ant = 1;
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
	}
}
