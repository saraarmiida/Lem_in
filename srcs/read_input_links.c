#include "../includes/lem_in.h"

void	add_room_to_rooms_linked_rooms(t_room *room, t_room *room2)
{
	t_rlink	*link;

	if (!(link = (t_rlink*)malloc(sizeof(t_rlink))))
	{
		ft_printf("Malloc error\n");
		return ;
	}
	link->room = room2;
	link->next = NULL;
	if (room->linked_rooms)
		link->next = room->linked_rooms;
	room->linked_rooms = link;
	link->visited = 0;
}

int		check_link(t_lem *lem, int i)
{
	while (ft_isprint(lem->input[i]) && lem->input[i] != '-')
		i++;
	if (lem->input[i] != '-')
		return (-2);
	i++;
	while (ft_isprint(lem->input[i]))
		i++;
	if (lem->input[i] != '\n')
		return (-2);
	lem->link_amount++;
	return (i + 1);
}

int		save_link(t_lem *lem, int i)
{
	t_room	*room;
	t_room	*room2;
	char	*from;
	char	*to;

	from = ft_strcdup(&lem->input[i], '-');
	i += ft_strlen(from) + 1;
	to = ft_strcdup(&lem->input[i], '\n');
	room = get_hashed_room(lem, from);
	room2 = get_hashed_room(lem, to);
	add_room_to_rooms_linked_rooms(room, room2);
	add_room_to_rooms_linked_rooms(room2, room);
	if (lem->visu_info == 1)
		ft_printf("Edge: %d | %d | %d | %d\n", room->x, room->y, room2->x, room2->y);
	return (i + ft_strlen(to) + 1);
}

int		get_links(t_lem *lem)
{
	int	i;

	i = lem->i;
	while (lem->input[i])
	{
		if (lem->input[i] == '#')
			i = skip_line(lem->input, i);
		else if ((check_link(lem, i)) != -2)
		{
			i = save_link(lem, i);
		}
		else
		{
			ft_printf("Links error\n");
			return (1);
		}
	}
	ft_printf("Got %d links\n", lem->link_amount);
	lem->i = i;
	return (0);
}
