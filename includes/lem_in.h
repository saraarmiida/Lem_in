#ifndef LEM_IN_H
# define LEM_IN_H

# define BUF_SIZE	4194305

typedef struct	s_room
{
	int			name;
	int			x;
	int			y;
	int			level;
	int			ant;
}				t_room;

typedef struct	s_lem
{
	t_room		**room;
	int			ants;		/*make unsigned long*/
	int			rooms;
	int			links;
	int			fd;
	char		*input;
}				t_lem;

int		bfs(int ants);

#endif