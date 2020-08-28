#include "../includes/lem_in.h"

void			print_table(t_lem *lem)
{
	int		i;
	t_room	*room;

	i = 0;
	while (i < lem->room_amount)
	{
		room = lem->rooms[i];
		if (room == NULL)
		{
			i++;
			continue ;
		}
		ft_printf("slot[%4d]: ", i);
		while (room != NULL)
		{
			ft_printf("Name: %d | X: %d | Y: %d | Next: %p\n", room->name, room->x, room->y, room->next);
			room = room->next;
		}
		ft_printf("\n");
		i++;
	}
}

t_entry			*pair(char *key, char *value)
{
	t_entry *entry;

	/* allocate space for key & value? */
	entry = (t_entry*)malloc(sizeof(t_entry));
	entry->key = key;
	entry->value = value;
	entry->next = NULL;
	return (entry);
}

// void			set_value(t_table *hashtable, char *key, char *value)
// {
// 	unsigned int	slot;
// 	t_entry			*entry;
// 	t_entry			*prev;

// 	slot = hash(key);
// 	entry = hashtable->entries[slot];
// 	if (entry == NULL)
// 	{
// 		hashtable->entries[slot] = pair(key, value);
// 		return ;
// 	}
// 	while (entry != NULL)
// 	{
// 		if (ft_strcmp(entry->key, key) == 0)
// 		{
// 			printf("Duplicate of %s found", value);
// 			return ;
// 		}
// 		prev = entry;
// 		entry = prev->next;
// 	}
// 	prev->next = pair(key, value);
// }

void			*create_table(t_lem *lem)
{
	int			i;
	t_room		**rooms;

	rooms = (t_room**)malloc(sizeof(t_room) * lem->room_amount);
	i = 0;
	while (i < lem->room_amount)
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

// void		make_hashtable(t_lem *lem)
// {
// 	t_table *ht;
// 	int		j;
// 	char	*name;

// 	ht = create_table(lem->room_amount);
// 	j = 0;
// 	while (j < lem->room_amount)
// 	{
// 		name = ft_itoa(lem->rooms[j]->name);
// 		set_value(ht, ft_itoa(j), name);
// 		j++;
// 	}
// 	print_table(ht);
// }