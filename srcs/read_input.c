#include "../includes/lem_in.h"

int		skip_line(char *input, int i)
{
	ft_printf("Skipping line\n");
	while (input[i] && input[i] != '\n')
		i++;
	return (i + 1);
}

int		get_ants(t_lem *lem)
{
	int	i;

	i = 0;
	ft_printf("getting ants\n");
	while (lem->input[i])
	{
		if (lem->input[i] == '#')
		{
			ft_printf("skip line\n");
			i += skip_line(lem->input, i);
		}
		else if (ft_isdigit(lem->input[i]) && (i == 0 || lem->input[i - 1] == '\n'))
		{
			lem->ants = ft_atoi(&lem->input[i]); /* check amount of ants */
			ft_printf("Got %d ants\n", lem->ants);
			return (i + ft_intlen(lem->ants) + 1);
		}
	}
	ft_printf("Ants error\n");
	return (1); /* add error message / exit here */
}

// int		save_room(t_lem *lem, int i)
// {
// 	t_room	*room;

// 	if (!(room = (t_room*)malloc(sizeof(t_room))))
// 		return (1);
// 	room->name = ft_strcdup(&lem->input[i], ' ');
// 	i += ft_strlen(room->name) + 1;
// 	room->x = ft_atoi(&lem->input[i]);
// 	i += ft_intlen(room->x) + 1;
// 	room->y = ft_atoi(&lem->input[i]);
// }

int		check_room(t_lem *lem, int i)
{
	ft_printf("Checking room\n");
	ft_printf("Check: %.4s\n", &lem->input[i]);
	while(ft_isprint(lem->input[i]) && lem->input[i] != ' ')
		i++;
	if (lem->input[i] != ' ')
	{
		ft_putstr(&lem->input[i]);
		ft_printf("Room format error 1\n");
		exit(0) ;
	}
	i++;
	while (ft_isdigit(lem->input[i]))
		i++;
	if (lem->input[i] != ' ')
	{
		ft_printf("Room format error 2\n");
		exit(0) ;
	}
	i++;
	while (ft_isdigit(lem->input[i]))
		i++;
	if (lem->input[i] != '\n')
	{
		ft_printf("Room format error 3\n");
		exit(0) ;
	}
	lem->rooms++;
	return (i + 1);
}

void	get_rooms(t_lem *lem)
{
	int	i;

	i = lem->i;
	while (lem->input[i])
	{
		if (lem->input[i] == '#')
			i += skip_line(lem->input, i);
		else
			i += check_room(lem, i);
	}
	ft_printf("rooms: %d\n", lem->rooms);
	// while (lem->input[i])
	// {
	// 	if (lem->input[i] == '#')
	// 		i += skip_line(lem->input, i);
	// 	else
	// 		i += save_room(lem, i);
	// }
}

int		read_input(t_lem *lem)
{
	char	buf[BUF_SIZE + 1];
	char	*tmp;
	int		i;

	while((i = read(lem->fd, buf, BUF_SIZE)) > 0)
	{
		buf[i] = '\0';
		if (!lem->input)
			lem->input = ft_strnew(0);
		tmp = ft_strjoin(lem->input, buf);
		ft_strdel(&lem->input);
		lem->input = tmp;
	}
	lem->i = get_ants(lem);
	get_rooms(lem);
	return (0);
}