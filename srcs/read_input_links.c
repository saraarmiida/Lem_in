#include "../includes/lem_in.h"

/*
** Add link to room
*/

int		add_link_to_room(t_room *room, char *linkfrom, char *linkto)
{
	int		i;

	i = 0;
	if(room == NULL)
		return (0);
	while (i < BAD_MAGIC_NUMBER_LINKS)
	{
		if ((room->links[i]->from == linkfrom && room->links[i]->to == linkto) ||
		(room->links[i]->from == linkto && room->links[i]->to == linkfrom)) // Check for doubles
			return (0);
		else if (room->links[i]->from == NULL)
		{
			room->links[i]->from = linkfrom;
			room->links[i]->to = linkto;
			return (1);
		}
		i++;
	}
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
** Create a link. Currently only supports rooms with
** integers as names and all must be unique.
** - save hash values instead of room names
*/

int		save_link(t_lem *lem, int i, int j)
{
	t_llink	*link;
	t_room	*room;
	int		k;

	k = 0;
	if (!(link = (t_llink*)malloc(sizeof(t_llink))))
		return (1);
	link->from = ft_strcdup(&lem->input[i], '-');
	i += ft_strlen(link->from) + 1;
	link->to = ft_strcdup(&lem->input[i], '\n');
	room = lem->rooms[hash(link->from, lem->room_amount)];
	lem->links[j] = link;
	if (add_link_to_room(room, link->from, link->to) == 0)
	{
		ft_printf("Failed to add link to room.\n");
		return (0);
	}
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