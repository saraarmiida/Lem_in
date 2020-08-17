#include "../includes/lem_in.h"
#include "../libft/ft_printf/includes/ft_printf.h"
#include <unistd.h>

void	init_lem(t_lem *lem)
{
	lem->fd = 0;
	lem->ants = 0;
	lem->links = 0;
	lem->rooms = 0;
	lem->input = NULL;
}

int		skip_comment(char *input, int i)
{
	while (input[i] && input[i] != '\n')
		i++;
	return (i);
}

int		get_ants(t_lem *lem)
{
	int	i;

	i = 0;
	while (lem->input[i])
	{
		if (lem->input[i] == '#')
			i += skip_comment(lem->input, i);
		else if (ft_isdigit(lem->input[i]) && (i == 0 || lem->input[i - 1] == '\n'))
		{
			lem->ants = ft_atoi(&lem->input[i]);
			ft_printf("%d\n", lem->ants);
			return (0);
		}
	}
	return (1);
}

int		read_input(t_lem *lem)
{
	char	buf[BUF_SIZE + 1];		/* gets segfault with BUF_SIZE for some reason */
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
	get_ants(lem);
	get_rooms(lem);
	return (0);
}

int		main()
{
	t_lem	*lem;

	if (!(lem = (t_lem*)malloc(sizeof(t_lem))))
		return (1);
	init_lem(lem);
	read_input(lem);
	return (0);
}