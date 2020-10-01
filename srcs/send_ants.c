#include "../includes/lem_in.h"

int		send_new_ants(t_paths *path, int ant)
{
	while (path != NULL)
	{
		ft_printf("L%d-%s ", ant, path->path->next->room->c_name);
		path->path->next->room->ant = ant;
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

void	send_ants(t_lem *lem)
{
	int		ant;
	int		ant_counter;
	t_paths	*path;
	t_paths	*start;

	ft_printf("%s\n\n", lem->input); // add ignoring comments
	ant = 1;
	ant_counter = 5;
	start = lem->paths;
	while (ant_counter > 0 || ant_counter == -1)
	{
		path = start;
		while (path != NULL)
		{
			move_ants(path->path->next, lem->end);
			path = path->next;
		}
		if (ant <= lem->ants)
		{
			ant = send_new_ants(start, ant);
		}
		ant_counter--;
		ft_printf("\n");
	}
}
