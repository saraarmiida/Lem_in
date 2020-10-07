#ifndef VISU_H
# define VISU_H

# define NODESIZE	20
# define PADDING	14
# define OFFSETX	550
# define OFFSETY	100
#include <stdio.h>
#include "../../includes/lem_in.h"

typedef struct	s_node
{
	int			x;
	int			y;
	int			name;
	int			level;
}				t_node;

typedef struct	s_line
{
	int			fromx;
	int			fromy;
	int			tox;
	int			toy;
}				t_line;

typedef struct	s_visu
{
	t_line		*lines;
	t_node		*nodes;
	int			room_amount;
	int			link_amount;
	TTF_Font	*font;
}				t_visu;

int	draw_nodes(SDL_Renderer *renderer, t_visu *visu);
int	draw_lines(SDL_Renderer *renderer, t_visu *visu);
int	draw_text(SDL_Renderer *renderer, t_visu *visu);

#endif