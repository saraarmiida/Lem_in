#include "../includes/lem_in.h"

int		skip_line(char *input, int i)
{
	while (input[i] && input[i] != '\n')
		i++;
	return (i + 1);
}

/*
** count the amount of ants
** - validate amount of ants
** - add error message
*/

int		get_ants(t_lem *lem)
{
	int	i;

	i = 0;
	while (lem->input[i])
	{
		if (lem->input[i] == '#')
		{
			i = skip_line(lem->input, i);
		}
		else if (ft_isdigit(lem->input[i]) && (i == 0 || lem->input[i - 1] == '\n'))
		{
			lem->ants = ft_atoi(&lem->input[i]);
			ft_printf("Got %d ants\n", lem->ants);
			lem->i = i + ft_intlen(lem->ants) + 1;
			return (0);
		}
	}
	ft_printf("Ants error\n");
	return (1);
}

/*
** create a room to be saved in struct
** - save hash value instead of room name
*/

int		save_room(t_lem *lem, int i, int j)
{
	t_room	*room;

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		return (1);
	room->name = ft_strcdup(&lem->input[i], ' ');
	i += ft_strlen(room->name) + 1;
	room->x = ft_atoi(&lem->input[i]);
	i += ft_intlen(room->x) + 1;
	room->y = ft_atoi(&lem->input[i]);
	lem->rooms[j] = room;
	return (i + ft_intlen(room->y) + 1);
}

/*
** validates room syntax
** - no rooms with same name
** - no rooms with same coordinate
** - add error message
*/

int		check_room(t_lem *lem, int i)
{
	int j;

	j = i;
	while (lem->input[j] != '\n' && lem->input[j])
	{
		if (lem->input[j] == '-')
			return (-1);
		j++;
	}
	while (ft_isprint(lem->input[i]) && lem->input[i] != ' ')
		i++;
	if (lem->input[i] != ' ')
		return (-2);
	i++;
	while (ft_isdigit(lem->input[i]))
		i++;
	if (lem->input[i] != ' ')
		return (-2);
	i++;
	while (ft_isdigit(lem->input[i]))
		i++;
	if (lem->input[i] != '\n')
		return (-2);
	lem->room_amount++;
	return (i + 1);
}

/*
** first count how many rooms and then save rooms to struct
** - error in case of wrongly formatted or duplicate room
** - save first linked list and afterwards reassign to t_room** when amount known?
** - save hash values instead of room names
** - chop shorter
** - save start and end rooms somehow
** - chop
*/

int		get_rooms(t_lem *lem)
{
	int	i;
	int	j;

	i = lem->i;
	while (lem->input[i])
	{
		if (lem->input[i] == '#')
			i = skip_line(lem->input, i);
		else
		{
			if ((i = check_room(lem, i)) == -1)
				break ;
			else if (i == -2)
			{
				ft_printf("Rooms error\n");
				return (1);
			}
		}
	}
	ft_printf("Got %d rooms\n", lem->room_amount);
	if (!(lem->rooms = (t_room**)malloc(sizeof(t_room) * lem->room_amount)))
		return (1);
	i = lem->i;
	j = 0;
	while (j < lem->room_amount)
	{
		if (lem->input[i] == '#')
			i = skip_line(lem->input, i);
		else
		{
			i = save_room(lem, i, j);
			j++;
		}
	}
	lem->i = i;
	return (0);
}

/*
** check correct syntax of link
** - validate room names
** - count only unique links
** - one or more links
*/

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

/*
** create a link
** - save hash values instead of room names
*/

int		save_link(t_lem *lem, int i, int j)
{
	t_llink	*link;

	if (!(link = (t_llink*)malloc(sizeof(t_llink))))
		return (1);
	link->from = ft_strcdup(&lem->input[i], '-');
	i += ft_strlen(link->from) + 1;
	link->to = ft_strcdup(&lem->input[i], '\n');
	link->visited = 0;
	lem->links[j] = link;
	return (i + ft_strlen(link->to) + 1);
}

/*
** first count how many links and then save links to struct
** to do:
** - ignore duplicate links
** - error message in case of syntax error etc
** - save to linked list?
** - save hash values instead of room names
** - chop shorter
*/

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
	if (!(lem->links = (t_llink**)malloc(sizeof(t_llink) * lem->link_amount)))
		return (1);
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

/*
** read input to a simple string
*/

int		read_input(t_lem *lem)
{
	char	buf[BUF_SIZE + 1];
	char	*tmp;
	int		i;

	while ((i = read(lem->fd, buf, BUF_SIZE)) > 0)
	{
		buf[i] = '\0';
		if (!lem->input)
			lem->input = ft_strnew(0);
		tmp = ft_strjoin(lem->input, buf);
		ft_strdel(&lem->input);
		lem->input = tmp;
	}
	get_ants(lem);
	get_rooms(lem);
	get_links(lem);
	return (0);
}
