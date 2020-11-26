
#include "../includes/lem_in.h"

/*
** Sends a new ant to the shortest path, then evaluates whether it makes
** sense to send another ant to the next shortest path. It makes sense to
** send an ant to a path if path length is less than length of the shorter
** paths combined with the amount of ants left.
*/

static int	send_new_ants(t_paths *path, int ant, t_lem *lem)
{
	int	length;
	int	i;

	i = 1;
	length = 0;
	while (path != NULL && ant <= lem->ants)
	{
		if (lem->quiet == 0)
			ft_printf("L%d-%s ", ant, path->path->next->room->name);
		path->path->next->room->ant = ant;
		if (path->length > lem->path_length)
			lem->path_length = path->length;
		length += path->length;
		path = path->next;
		if (path != NULL && (length + (lem->ants - ant)) / i < path->length)
			return (ant + 1);
		ant++;
		i++;
	}
	return (ant);
}

/*
** Goes through all rooms in a path, and if there is an ant in a room, it
** moves the ant to the next room.
*/

static void	move_ants(t_path *room, t_room *end, int quiet)
{
	int	temp_ant;
	int	running_ant;

	running_ant = 0;
	while (room->room != end)
	{
		if (room->room->ant != 0)
		{
			if (quiet == 0)
				ft_printf("L%d-%s ", room->room->ant, room->next->room->name);
		}
		temp_ant = room->room->ant;
		room->room->ant = running_ant;
		running_ant = room->next->room == end ? 0 : temp_ant;
		room = room->next;
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

void		print_flags(t_lem *lem, int lines)
{
	char	*str;

	str = NULL;
	if (lem->print_set == 1)
		print_path(lem->best_set);
	if (lem->print_links == 1)
		ft_printf("lines: %d\n", lines);
	if (lem->required == 1)
	{
		str = ft_strstr(lem->input, "#Here is the number of lines required: ");
		if (str == NULL)
			str = "not available";
		else
			str = ft_strcdup(str + 39, '\n');
		ft_printf("number of lines required: %s\n", str);
		
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
	t_paths	*path;
	int		ant;
	int		i;

	ant = 1;
	i = 0;
	if (lem->quiet == 0)
		ft_printf("%s\n", lem->input);
	sort_paths(lem->best_set->paths);
	lem->path_length = lem->best_set->paths->length;
	while (lem->path_length > 0)
	{
		path = lem->best_set->paths;
		while (path != NULL)
		{
			move_ants(path->path->next, lem->end, lem->quiet);
			path = path->next;
		}
		if (ant <= lem->ants)
			ant = send_new_ants(lem->best_set->paths, ant, lem);
		lem->path_length--;
		if (lem->quiet == 0)
			ft_printf("\n");
		i++;
	}
	print_flags(lem, i);
}
