#include "../includes/lem_in.h"

void			*init_table(t_lem *lem)
{
	int			i;
	t_room		**rooms;

	rooms = (t_room**)malloc(sizeof(t_room) * (lem->tablesize + 5));
	i = 0;
	while (i < lem->tablesize)
	{
		rooms[i] = NULL;
		i++;
	}
	return (rooms);
}

unsigned int	hash(char *key, int tablesize)
{
	unsigned long int	value;
	unsigned int		i;
	unsigned int		key_len;

	value = 0;
	i = 0;
	key_len = ft_strlen(key);
	while (i < key_len)
	{
		value = value * 37 + key[i];
		i++;
	}
	value = value % tablesize;
	return (value);
}
