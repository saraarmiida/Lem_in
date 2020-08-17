/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spentti <spentti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 09:23:47 by spentti           #+#    #+#             */
/*   Updated: 2020/08/12 13:20:01 by spentti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_to_line(char **str, char **line, int fd)
{
	char	*temp;
	int		len;

	len = 0;
	while (str[fd][len] != '\n' && str[fd][len] != '\0')
		len++;
	if (!(*line = ft_strndup(str[fd], len)))
		return (-1);
	if (str[fd][len] == '\n' && str[fd][len + 1] != '\0')
	{
		temp = ft_strdup(str[fd] + len + 1);
		free(str[fd]);
		str[fd] = temp;
	}
	else if (str[fd][len] == '\0' || str[fd][len + 1] == '\0')
		ft_strdel(&str[fd]);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	int			j;
	char		buf[BUFF_SIZE + 1];
	static char	*str[FD_MAX];
	char		*temp;

	if (fd < 0 || !line)
		return (-1);
	while ((j = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[j] = '\0';
		if (!str[fd])
			if (!(str[fd] = ft_strnew(0)))
				return (-1);
		if (!(temp = ft_strjoin(str[fd], buf)))
			return (-1);
		free(str[fd]);
		str[fd] = temp;
		if ((ft_strchr(buf, '\n')))
			break ;
	}
	if (j < 0)
		return (-1);
	if (str[fd] == NULL || str[fd][0] == '\0')
		return (0);
	return (str_to_line(str, line, fd));
}
