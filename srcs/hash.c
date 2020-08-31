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
