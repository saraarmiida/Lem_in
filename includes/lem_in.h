#ifndef LEM_IN_H
# define LEM_IN_H

# define BUF_SIZE	4194305
# include "../libft/ft_printf/includes/ft_printf.h"
# include <unistd.h>

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
	int				ants;		/*make unsigned long*/
	int				room_amount;
	int				link_amount;
	int				fd;
	char			*input;
	int				i;
}					t_lem;

/* read_input.c */

int					read_input(t_lem *lem);

int		bfs(int ants);

#endif