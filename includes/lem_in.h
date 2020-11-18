#ifndef LEM_IN_H
# define LEM_IN_H

# define TABLE_SIZE	100
# define BUF_SIZE	4194305
# define BAD_MAGIC_NUMBER_LINKS 10
# define MAX_INT	2147483647
# include "../libft/ft_printf/includes/ft_printf.h"
# include <unistd.h>
# include <fcntl.h>
// # include "SDL2/SDL.h"
// # include "../visualiser/SDL2_ttf.framework/Headers/SDL_ttf.h"

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

typedef struct		s_queue
{
	struct s_room	*room;
	struct s_rlink	*edge;
	struct s_queue	*parent;
	struct s_queue	*next;
}					t_queue;

typedef struct		s_paths
{
	struct s_path	*path;
	int				length;
	struct s_paths	*next;
}					t_paths;

typedef struct		s_bucket
{
	struct s_paths	*paths;
	int				length;
	int				flow;
	int				cost;
}					t_bucket;

/*
** Combine t_path, t_rlink, t_queues and t_paths to t_queue.
*/

// typedef struct		s_queue
// {
// 	void			*node;
// 	size_t			node_size;
// 	void			*next;
// 	void			*prev;
// }					t_queue;

typedef struct		s_room
{
	char			*c_name;
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
	t_queue			*queue;
	t_bucket		*best_set;
	t_paths			*paths;
	int				start_i;
	int				end_i;
	int				max_flow;
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
t_queue				*init_newq(t_room *room, t_rlink *edge, t_queue *parent);
t_path				*init_node(t_room *room, t_path *next);
void				*init_table(t_lem *lem);

/*
** bfs.c
*/
int					create_bucket(t_lem *lem);
int					solve(t_lem *lem);

/*
** find_paths.c
*/
t_path				*add_path_to_bucket(t_lem *lem, t_bucket *bucket);

/*
** send_ants.c
*/
void				send_ants(t_lem *lem);

/*
** print_info.c
*/
void				print_queue(t_queue *queue, int l);
void				print_path(t_bucket *set);
void				print_debug_info(t_lem *lem);
void				print_paths(t_lem *lem);

void				ft_error(char *msg);

#endif
