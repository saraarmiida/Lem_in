/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraarmiida <saraarmiida@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:10:42 by saraarmiida       #+#    #+#             */
/*   Updated: 2020/12/14 13:10:45 by saraarmiida      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# define TABLE_SIZE	100
# define BUF_SIZE	4194305
# define BAD_MAGIC_NUMBER_LINKS 10
# define MAX_INT	2147483647
# include "../libft/ft_printf/includes/ft_printf.h"
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

typedef struct		s_path
{
	struct s_room	*room;
	struct s_path	*next;
	struct s_path	*prev;
	int				length;
}					t_path;

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

typedef struct		s_queue
{
	struct s_room	*room;
	struct s_rlink	*edge;
	struct s_queue	*parent;
	struct s_queue	*next;
	struct s_queue	*prev;

}					t_queue;

typedef struct		s_rlink
{
	struct s_room	*tgtroom;
	struct s_rlink	*next;
	struct s_rlink	*opp;
	int				flow;
}					t_rlink;

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				level;
	int				visited;
	int				in_path;
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
	t_queue			*last_queue;
	t_path			**ant;
	char			*input;
	int				start_i;
	int				end_i;
	int				max_flow;
	int				path_length;
	long long int	ants;
	int				room_nb;
	int				tablesize;
	int				link_nb;
	int				i;
	int				j;
	int				info;
	int				print_lines;
	int				print_set;
	int				quiet;
	int				required;
	int				leaks;
}					t_lem;

/*
** read_input_basics.c
*/
int					read_input(t_lem *lem);

/*
** read_input_rooms.c
*/
int					get_rooms(t_lem *lem);

/*
** read_input_links.c
*/
int					get_links(t_lem *lem);

/*
** check_rooms.c
*/
void				check_rooms(t_lem *lem);

/*
** hash.c
*/
unsigned int		hash(char *key, int tablesize);
t_room				*get_hashed_room(t_lem *lem, char *key);

/*
** solve.c
*/
int					solve(t_lem *lem);

/*
** edmondskarp.c
*/

int					edmondskarp(t_lem *lem);

/*
** send_ants.c
*/
void				send_ants(t_lem *lem);

/*
** flags.c
*/
void				handle_flags(int argc, char **argv, t_lem *lem);
void				print_flags(t_lem *lem, int lines);

/*
** utils.c
*/
void				reset_rooms(t_lem *lem);
int					ft_strmatchlen(char const *s, char const *s2);
void				ft_error(char *msg);
int					skip_line(char *input, int i);

/*
** inits.c
*/
t_path				*init_node(t_room *room, t_path *next, t_lem *lem, int len);
t_queue				*init_newq(t_room *r, t_rlink *edge, t_queue *p, t_lem *l);
void				*init_table(t_lem *lem);
void				init_lem(t_lem *lem);
t_path				**init_ants(int ants);

/*
** free.c
*/
void				free_path(t_path *node);
void				free_set(t_bucket *set);
void				free_queue(t_queue *queue);

/*
** print_info.c
*/
// remove ones that are not necessary for visu / explaining
void				print_path(t_bucket *set);
void				print_set(t_bucket *set);
void				print_room_visu(t_room *room);
void				print_edge_visu(t_rlink *edge, char c);

void				ft_error(char *msg);

#endif
