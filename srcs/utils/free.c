#include "../includes/lem_in.h"

void	free_path(t_path *node)
{
	t_path *tmp;

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
