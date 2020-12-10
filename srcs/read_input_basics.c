#include "../includes/lem_in.h"

static int	only_digits(char *input, int index)
{
	int	i;

	i = index;
	while (input[i] != '\n')
	{
		if (ft_isdigit(input[i]) == 0)
			ft_error("invalid ants");
		i++;
	}
	return (1);
}

static int	get_ants(t_lem *lem)
{
	int		i;
	int		n;
	char	*str;

	i = 0;
	while (lem->input[i] && lem->input[i] == '#')
		i = skip_line(lem->input, i);
	if (only_digits(lem->input, i) && (i == 0 || lem->input[i - 1] == '\n'))
	{
		lem->ants = ft_atoi(&lem->input[i]);
		n = ft_intlen(lem->ants);
		str = ft_itoa(lem->ants);
		if (ft_strncmp(str, &lem->input[i], n) != 0)
			ft_error("invalid number of ants");
		lem->i = i + ft_intlen(lem->ants) + 1;
		if (lem->ants < 1)
			ft_error("invalid number of ants");
	}
	else
		ft_error("invalid ants");
	return (1);
}

/*
** read input to a simple string
*/

int			read_input(t_lem *lem)
{
	char	buf[BUF_SIZE + 1];
	char	*tmp;
	int		i;

	while ((i = read(0, buf, BUF_SIZE)) > 0)
	{
		buf[i] = '\0';
		if (lem->input == NULL)
			lem->input = ft_strnew(0);
		tmp = ft_strjoin(lem->input, buf);
		ft_strdel(&lem->input);
		lem->input = tmp;
	}
	if (i == -1)
		ft_error(strerror(errno));
	if (lem->input == NULL)
		ft_error("empty input file");
	get_ants(lem);
	get_rooms(lem);
	get_links(lem);
	return (0);
}
