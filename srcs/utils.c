#include "../includes/lem_in.h"

/*
** Sets all rooms to be unvisited.
*/

void	reset_rooms(t_lem *lem)
{
	int		i;
	t_room	*r;

	i = 0;
	while (i < lem->tablesize)
	{
		r = lem->rooms[i];
		if (r != NULL)
		{
			if (r->visited == 1)
				r->visited = 0;
			if (r->in_path == 0)
				r->level = 0;
			while (r->next != NULL)
			{
				r = r->next;
				if (r->visited == 1)
					r->visited = 0;
				if (r->in_path == 0)
					r->level = 0;
			}
		}
		i++;
	}
	lem->start->visited = 0;
	lem->end->visited = 0;
}

/*
** ft_strmatchlen takes haystack and needle and
** returns the number of indexes the haystack had to
** search plus the length of needle. If needle is
** not found, it returns -1.
*/

int		ft_strmatchlen(char const *s, char const *s2)
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

void	ft_error(char *msg)
{
	ft_printf("ERROR: %s\n", msg);
	exit(1);
}

void	free_links(t_rlink *node)
{
	t_rlink *tmp;

	while (node != NULL)
	{
		tmp = node;
		node = node->next;
		free(tmp);
	}
}

void	free_lem(t_lem *lem)
{
	int		i;
	t_room	*r;
	t_room	*tmp;

	i = 0;
	// ft_printf("freeing struct\n");
	while (i < lem->tablesize)
	{
		r = lem->rooms[i];
		if (r != NULL)
		{
			free_links(r->linked_rooms);
			tmp = r;
			r = r->next;
			ft_strdel(&tmp->c_name);
			free(tmp);
			while (r != NULL)
			{
				free_links(r->linked_rooms);
				tmp = r;
				r = r->next;
				ft_strdel(&tmp->c_name);
				free(tmp);
			}
		}
		i++;
	}
	free(lem->rooms);
	ft_strdel(&lem->input);
	free(lem);
}

void	free_path(t_path *node)
{
	t_path *tmp;

	// ft_printf("freeing path\n");
	while (node != NULL)
	{
		tmp = node;
		node = node->next;
		free(tmp);
	}
}

void	free_set(t_bucket *set)
{
	t_paths *path;
	t_paths	*tmp;

	path = set->paths;
	// ft_printf("freeing set\n");
	while (path != NULL)
	{
		free_path(path->path);
		tmp = path;
		path = path->next;
		free(tmp);
	}
	free(set);
	set = NULL;
}

void	free_queue(t_queue *queue)
{
	t_queue	*tmp;

	// ft_printf("freeing queue\n");
	while (queue != NULL)
	{
		if (queue)
		{
			tmp = queue;
			queue = queue->prev;
			if (tmp)
				free(tmp);
		}
	}
}
