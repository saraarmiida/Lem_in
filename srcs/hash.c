#include "../includes/lem_in.h"

void			*init_table(t_lem *lem)
{
	int			i;
	t_room		**rooms;

	rooms = (t_room**)malloc(sizeof(t_room) * (lem->tablesize));
	i = 0;
	while (i < lem->tablesize)
	{
		rooms[i] = NULL;
		i++;
	}
	return (rooms);
}

/*
** Attempts to make a unique hash value to key
*/

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

/*
** Tries to find the room the the name "key" from the hashtable
*/

t_room 			*get_hashed_room(t_lem *lem, char *key)
{
    unsigned int	slot;
	t_room			*room;
	
	slot = hash(key, lem->tablesize);
	room = lem->rooms[slot];
    if (room == NULL)
        return (NULL);
    while (room != NULL)
	{
        if (ft_strcmp(room->c_name, key) == 0)
            return (room);
        room = room->next;
    }
    return (NULL);
}
