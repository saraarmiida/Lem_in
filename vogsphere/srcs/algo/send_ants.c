/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spentti <spentti@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:18:25 by spentti           #+#    #+#             */
/*   Updated: 2020/12/26 17:34:32 by spentti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

/*
** Sends a new ant to the shortest path and saves
** the room where the ant is to ant struct. Then evaluates wheter it makes
** sense to send another ant to the next shortest path. It makes sense to
** send an ant to a path if path length is less than average length of the
** shorter paths combined with the amount of ants left.
*/

static int	send_new_ants(t_paths *path, int ant, t_lem *lem)
{
	int	n;
	int	paths;

	paths = 1;
	n = 0;
	while (path != NULL && ant <= lem->ants)
	{
		ft_printf("L%d-%s ", ant, path->path->next->room->name);
		if (path->length > lem->path_length)
			lem->path_length = path->length;
		n += path->length;
		if (path->path->next->room != lem->end)
		{
			lem->ant[ant - 1] = path->path->next;
			path = path->next;
			if (path != NULL && (n + (lem->ants - ant)) / paths < path->length)
				return (ant + 1);
		}
		ant++;
		paths++;
	}
	return (ant);
}

/*
** Goes through the ant struct and if ant is already in a path, moves it
** one room forward. When ant has reached end room, it gets set back to NULL.
*/

static void	move_ants(t_lem *lem, int last_ant)
{
	t_path	**ant;
	int		i;

	ant = lem->ant;
	i = 0;
	while (i < last_ant)
	{
		if (ant[i] != NULL)
		{
			ft_printf("L%d-%s ", i + 1, ant[i]->next->room->name);
			if (ant[i]->next->room != lem->end)
				ant[i] = ant[i]->next;
			else
				ant[i] = NULL;
		}
		i++;
	}
}

/*
** sorts paths from shortest to longest
*/

static void	sort_paths(t_paths *set)
{
	int		temp_length;
	t_path	*temp_path;
	t_paths	*current;
	t_paths	*next;

	current = set;
	while (current->next != NULL)
	{
		next = current->next;
		while (next != NULL)
		{
			if (current->length > next->length)
			{
				temp_length = current->length;
				temp_path = current->path;
				current->path = next->path;
				current->length = next->length;
				next->path = temp_path;
				next->length = temp_length;
			}
			next = next->next;
		}
		current = current->next;
	}
}

/*
** Keeps track of how many rounds are still needed to get the latest sent
** ant to end room (lem->path_length) and while it is > 0, we move all ants that
** are currently on paths and if there are still ants in the start room, we
** send new ants to paths.
*/

void		send_ants(t_lem *lem)
{
	int		ant;
	int		lines;

	ant = 1;
	lines = 0;
	if (lem->quiet == 0)
		ft_printf("%s\n", lem->input);
	sort_paths(lem->best_set->paths);
	lem->path_length = lem->best_set->paths->length;
	lem->ant = init_ants(lem->ants);
	while (lem->path_length > 0 || ant <= lem->ants)
	{
		move_ants(lem, ant - 1);
		if (ant <= lem->ants)
			ant = send_new_ants(lem->best_set->paths, ant, lem);
		lem->path_length--;
		ft_printf("\n");
		lines++;
	}
	print_flags(lem, lines);
}
