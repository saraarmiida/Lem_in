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

int		save_link(t_lem *lem, int i, int j)
{
	t_room	*room;
	t_room	*room2;
	char	*from;
	char	*to;
	int		k;

	k = 0;
	from = ft_strcdup(&lem->input[i], '-');
	i += ft_strlen(from) + 1;
	to = ft_strcdup(&lem->input[i], '\n');
	room = get_hashed_room(lem, from);
	room2 = get_hashed_room(lem, to);
	j = 0;
	add_room_to_rooms_linked_rooms(room, room2);
	add_room_to_rooms_linked_rooms(room2, room);
	return (i + ft_strlen(to) + 1);
}

int		get_links(t_lem *lem)
{
	int	i;
	int	j;

	i = lem->i;
	while (lem->input[i])
	{
		if (lem->input[i] == '#')
			i = skip_line(lem->input, i);
		else if ((i = check_link(lem, i)) == -2)
		{
			ft_printf("Links error\n");
			return (1);
		}
	}
	ft_printf("Got %d links\n", lem->link_amount);
	i = lem->i;
	j = 0;
	while (j < lem->link_amount)
	{
		if (lem->input[i] == '#')
			i = skip_line(lem->input, i);
		else
		{
			i = save_link(lem, i, j);
			j++;
		}
	}
	lem->i = i;
	return (0);
}
