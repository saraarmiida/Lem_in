#include "../includes/lem_in.h"

t_rlink	*add_room_to_rooms_linked_rooms(t_room *room, t_room *room2)
{
	t_rlink	*link;

	if (!(link = (t_rlink*)malloc(sizeof(t_rlink))))
	{
		ft_printf("Malloc error\n");
		return (NULL);
	}
	link->tgtroom = room2;
	link->next = NULL;
	if (room->linked_rooms)
		link->next = room->linked_rooms;
	room->linked_rooms = link;
	link->flow = 0;
	link->opposite = NULL;
	return (link);
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
	t_room	*room1;
	t_room	*room2;
	t_rlink	*link1;
	t_rlink	*link2;
	char	*room_name;

	room_name = ft_strcdup(&lem->input[i], '-');
	i += ft_strlen(room_name) + 1;
	room1 = get_hashed_room(lem, room_name);
	room_name = ft_strcdup(&lem->input[i], '\n');
	i += ft_strlen(room_name) + 1;
	room2 = get_hashed_room(lem, room_name);
	if (room1 == NULL || room2 == NULL)
		ft_error("unknown room name in link");
	link1 = add_room_to_rooms_linked_rooms(room1, room2);
	link2 = add_room_to_rooms_linked_rooms(room2, room1);
	link1->opposite = link2;
	link2->opposite = link1;
	if (lem->info == 1)
	{
		ft_printf("|-\t-|Edge: %d | %d | %d | %d | from: %s to %s\n", room1->x, room1->y, room2->x, room2->y, room1->c_name, room2->c_name);
		ft_printf("|-\t-|Edge: %d | %d | %d | %d | from: %s to %s\n", room2->x, room2->y, room1->x, room1->y, room2->c_name, room1->c_name);
	}
	return (i);
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
			ft_error("invalid links");
	}
	lem->i = i;
	return (0);
}
