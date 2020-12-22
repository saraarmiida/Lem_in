/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spentti <spentti@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:19:50 by spentti           #+#    #+#             */
/*   Updated: 2020/12/22 12:10:08 by spentti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

static void	reset_room(t_room *r)
{
	if (r->visited == 1)
		r->visited = 0;
	if (r->in_path == 0)
		r->level = 0;
}

/*
** Sets all rooms to be unvisited.
*/

void		reset_rooms(t_lem *lem)
{
	int		i;
	t_room	*r;

	i = 0;
	while (i < lem->tablesize)
	{
		r = lem->rooms[i];
		if (r != NULL)
		{
			reset_room(r);
			while (r->next != NULL)
			{
				r = r->next;
				reset_room(r);
			}
		}
		i++;
	}
	lem->start->visited = 0;
	lem->end->visited = 0;
	if (lem->info == 1)
		ft_printf("#rn|");
}

/*
** ft_strmatchlen takes haystack and needle and
** returns the number of indexes the haystack had to
** search plus the length of needle. If needle is
** not found, it returns -1.
*/

int			ft_strmatchlen(char const *s, char const *s2)
{
	int i;
	int j;

	i = 0;
	while (s[i] != '\0')
	{
		j = 0;
		while (s[i] != s2[0] && s[i] != '\0')
			i++;
		while (s[i] == s2[j])
		{
			i++;
			j++;
		}
		if (s2[j] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

void		ft_error(char *msg)
{
	ft_printf("ERROR: %s\n", msg);
	exit(1);
}

int			skip_line(char *input, int i)
{
	while (input[i] && input[i] != '\n')
		i++;
	return (i + 1);
}
