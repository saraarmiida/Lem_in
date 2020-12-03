
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
	int	prev_paths;

	prev_paths = 1;
	length = 0;
	while (path != NULL && ant <= lem->ants)
	{
		if (lem->quiet == 0)
			ft_printf("L%d-%s ", ant, path->path->next->room->name);
		if (path->path->next->room != lem->end)	
			lem->ant[ant - 1] = path->path->next;
		else
			lem->ant[ant - 1] = NULL;
		if (path->length > lem->path_length)
			lem->path_length = path->length;
		length += path->length;
		path = path->next;
		if (path != NULL && (length + (lem->ants - ant)) / prev_paths < path->length)
			return (ant + 1);
		ant++;
		prev_paths++;
	}
	return (ant);
}

/*
** Goes through all rooms in a path, and if there is an ant in a room, it
** moves the ant to the next room.
*/

static void	move_ants(t_lem *lem)
{
	t_path	**ant;
	int		i;

	ant = lem->ant;
	i = 0;
	while (i < lem->ants)
	{
		if (ant[i] != NULL)
		{
			if (lem->quiet == 0)
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

t_path		**init_ants(int ants)
{
	t_path	**ant;
	int		i;

	i = 0;
	if (!(ant = (t_path**)malloc(sizeof(t_path*) * ants)))
		ft_error(strerror(errno));
	while (i < ants)
	{
		ant[i] = NULL;
		i++;
	}
	return (ant);
}

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
		move_ants(lem);
		if (ant <= lem->ants)
			ant = send_new_ants(lem->best_set->paths, ant, lem);
		lem->path_length--;
		if (lem->quiet == 0)
			ft_printf("\n");
		lines++;
	}
	print_flags(lem, lines);
}
