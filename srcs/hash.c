#include "../includes/lem_in.h"

void			print_table(t_table *hashtable)
{
	int		i;
	t_entry	*entry;

	i = 0;
	entry = hashtable->entries[i];
	while (i < TABLE_SIZE)
	{
		if (entry == NULL)
			continue ;
		printf("slot[%4d]: ", i);
		while (entry != NULL)
		{
			printf("%s=%s", entry->key, entry->value);
			entry = entry->next;
		}
		printf("\n");
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

void			set_value(t_table *hashtable, char *key, char *value)
{
	unsigned int	slot;
	t_entry			*entry;
	t_entry			*prev;

	slot = hash(key);
	entry = hashtable->entries[slot];
	if (entry == NULL)
	{
		hashtable->entries[slot] = pair(key, value);
		return ;
	}
	while (entry != NULL)
	{
		if (ft_strcmp(entry->key, key) == 0)
		{
			printf("Duplicate of %s found", value);
			return ;
		}
		prev = entry;
		entry = prev->next;
	}
	prev->next = pair(key, value);
}

t_table			*create_table(void)
{
	t_table		*hashtable;
	int			i;

	hashtable = (t_table*)malloc(sizeof(t_table));
	hashtable->entries = (t_entry**)malloc(sizeof(t_entry*) * TABLE_SIZE);
	i = 0;
	while (i < TABLE_SIZE)
	{
		hashtable->entries[i] = NULL;
		i++;
	}
	return (hashtable);
}

unsigned int	hash(char *key)
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
	value = value % TABLE_SIZE;
	return (value);
}

void		test_hash(void)
{
	t_table *ht;

	printf("here");
	ht = create_table();
	set_value(ht, "name1", "kisuli");
	set_value(ht, "name2", "koiruli");
	set_value(ht, "name3", "fisu");
	set_value(ht, "name4", "fretti");
	set_value(ht, "name5", "heponen");
	set_value(ht, "name6", "pupu");
	print_table(ht);
}