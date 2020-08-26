#include "../includes/lem_in.h"

int		skip_line(char *input, int i)
{
	while (input[i] && input[i] != '\n')
		i++;
	return (i + 1);
}

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
	char	*from;
	char	*to;

	if (!(link = (t_llink*)malloc(sizeof(t_llink))))
		return (1);
	from = ft_strcdup(&lem->input[i], '-');
	i += ft_strlen(link->from) + 1;
	to = ft_strcdup(&lem->input[i], '\n');
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
