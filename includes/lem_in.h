#ifndef LEM_IN_H
# define LEM_IN_H

# define TABLE_SIZE	100000
# define BUF_SIZE	4194305
# define START_ROOM	1
# define END_ROOM	2
# include "../libft/ft_printf/includes/ft_printf.h"
# include <unistd.h>
# include <fcntl.h>

typedef struct		s_entry
{
	char			*key;
	char			*value;
	struct s_entry	*next;
}					t_entry;

typedef struct		s_table
{
	t_entry			**entries;
}					t_table;


typedef struct		s_llink
{
	int				from;
	int				to;
	int				visited;
}					t_llink;

typedef struct		s_room
{
	int				name;
	int				x;
	int				y;
	int				level;
	int				ant;
	struct s_room	*next;
}					t_room;

typedef struct	s_lem
{
	t_room			**rooms;
	t_llink			**links;
	t_room			*start;
	t_room			*end;
	int				ants;		/*make unsigned long*/
	int				room_amount;
	int				link_amount;
	int				fd;
	char			*input;
	int				i;
	int				j;
}					t_lem;

typedef struct	s_route
{
	t_room			**rooms;
	t_llink			**links;
}					t_route;

/* read_input_basics.c */
int					read_input(t_lem *lem);
int					skip_line(char *input, int i);

/* read_input_rooms.c */
int					get_rooms(t_lem *lem);
int					get_start_and_end(t_lem *lem);

/* hash.c */
void				test_hash(void);
unsigned int		hash(char *key);
t_table				*create_table(void);
void				set_value(t_table *hashtable, char *key, char *value);

#endif
