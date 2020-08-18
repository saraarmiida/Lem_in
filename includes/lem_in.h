#ifndef LEM_IN_H
# define LEM_IN_H

# define BUF_SIZE	4194305
# include "../libft/ft_printf/includes/ft_printf.h"
# include <unistd.h>

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
	t_room			**room;
	int				ants;		/*make unsigned long*/
	int				rooms;
	int				links;
	int				fd;
	char			*input;
	int				i;
}					t_lem;

/* read_input.c */

int					read_input(t_lem *lem);


#endif