#include "../includes/lem_in.h"

void	send_ants(t_lem *lem)
{
	int		ant;
	int		ant_counter;
	t_paths	*path;
	t_path	*room;
	t_paths	*start;
	int		running_ant;
	int		temp_ant;
	int		loop_ant;

	ft_printf("%s\n\n", lem->input); // add ignoring comments
	ant = 1;
	ant_counter = -1;
	start = lem->paths;
	running_ant = 0;
	while (ant_counter > 0 || ant_counter == -1)
	{
		path = start;
		loop_ant = ant;
		while (path != NULL && loop_ant > 0)
		{
			room = path->path->next;
			while (room->room != lem->end && loop_ant > 0)
			{
				if (room->room->ant != 0)
				{
					ft_printf("L%d-%s ", room->room->ant, room->next->room->c_name);
					loop_ant--;
				}
				temp_ant = room->room->ant;
				room->room->ant = running_ant;
				running_ant = room->next->room == lem->end ? 0 : temp_ant;
				room = room->next;
			}
			path = path->next;
		}
		if (ant <= lem->ants)
		{
			path = start;
			while (path != NULL && ant <= lem->ants)
			{
				ft_printf("L%d-%s ", ant, path->path->next->room->c_name);
				path->path->next->room->ant = ant;
				ant++;
				ant_counter = path->length;
				path = path->next;
			}
		}
		ant_counter--;
		ft_printf("\n");
	}
}
