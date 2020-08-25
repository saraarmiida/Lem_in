#ifndef LEM_IN_H
# define LEM_IN_H

# define BUF_SIZE	4194305
# define START_ROOM	1
# define END_ROOM	2
# include "../libft/ft_printf/includes/ft_printf.h"
# include <unistd.h>
# include <fcntl.h>

typedef struct		s_llink
{
	char			*from;
	char			*to;
	int				visited;
}					t_llink;

typedef struct		s_room
{
	char			*name;
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

#endif