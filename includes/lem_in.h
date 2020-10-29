#ifndef LEM_IN_H
# define LEM_IN_H

# define TABLE_SIZE	100
# define BUF_SIZE	4194305
# define START_ROOM	1
# define END_ROOM	2
# define BAD_MAGIC_NUMBER_LINKS 10
# include "../libft/ft_printf/includes/ft_printf.h"
# include <unistd.h>
# include <fcntl.h>
# include "SDL2/SDL.h"
# include "../visualiser/SDL2_ttf.framework/Headers/SDL_ttf.h"

typedef struct		s_path
{
	struct s_room	*room;
	struct s_path	*next;
	struct s_path	*prev;
	int				length;
}					t_path;

typedef struct		s_rlink
{
	struct s_room	*tgtroom;
	struct s_rlink	*next;
	struct s_rlink	*opposite;
	int				flow;
}					t_rlink;

typedef struct		s_queues
{
	struct s_rlink	*linked_rooms;
	struct s_queues	*nextq;
	struct s_queues	*prevq;
}					t_queues;

typedef struct		s_paths
{
	struct s_path	*path;
	int				length;
	struct s_paths	*next_path;
}					t_paths;

typedef struct		s_bucket
{
	struct s_paths	*paths;
	struct s_path	*path;
	int				length;
	struct s_bucket	*next_bucket;
}					t_bucket;

/*
** Combine t_path, t_rlink, t_queues and t_paths to t_queue.
*/

typedef struct		s_queue
{
	void			*node;
	size_t			node_size;
	void			*next;
	void			*prev;
}					t_queue;

typedef struct		s_room
{
	char			*c_name;
	int				name;
	int				x;
	int				y;
	int				level;
	int				visited;
	int				ant;
	t_rlink			*linked_rooms;
	struct s_room	*next;
}					t_room;

typedef struct		s_lem
{
	t_room			**rooms;
	t_room			*start;
	t_room			*end;
	t_room			*current;
	t_queues		**queues;
	t_bucket		*bucketlist;
	int				path_length;
	int				ants; // make unsigned long
	int				room_amount;
	int				tablesize;
	int				link_amount;
	int				fd;
	char			*input;
	int				i;
	int				j;
	int				info;
	int				lvl_flow;
}					t_lem;

/*
** read_input_basics.c
*/
int					read_input(t_lem *lem);
int					skip_line(char *input, int i);

/*
** read_input_rooms.c
*/
int					get_rooms(t_lem *lem);
int					get_start_and_end(t_lem *lem);

/*
** read_input_links.c
*/
int					get_links(t_lem *lem);

/*
** hash.c
*/
unsigned int		hash(char *key, int tablesize);
void				*init_table(t_lem *lem);
t_room				*get_hashed_room(t_lem *lem, char *key);

/*
** inits.c
*/
void				init_lem(t_lem *lem);
t_queues			*init_newq(t_queues *temp_prevq, t_room *current);
t_path				*init_new_path(t_lem *lem);
void				*init_table(t_lem *lem);

/*
** bfs.c
*/
int					create_bucket(t_lem *lem);

/*
** find_paths.c
*/
t_path			*add_path_to_bucket(t_lem *lem, t_bucket *bucket);

/*
** send_ants.c
*/
void				send_ants(t_lem *lem);

void				print_debug_info(t_lem *lem);
void				print_paths(t_lem *lem);

#endif
