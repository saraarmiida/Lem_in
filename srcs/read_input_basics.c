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
			lem->i = i + ft_intlen(lem->ants) + 1;
			return (0);
		}
	}
	ft_printf("Ants error\n");
	return (1);
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
