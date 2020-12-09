#ifndef VISU_H
# define VISU_H

# define NODESIZE	60
# define PADDING	60
# define FONTSIZE	24
# define OFFSETX	700
# define OFFSETY	100
# define DRAW_EDGE	1
# define DRAW_NODE	2
# define DRAW_TEXT	3
# define DRAW_PATH	4
# define DRAW_FPTH	5
# include <stdio.h>
# include "../../includes/lem_in.h"
# include "SDL2/SDL.h"
# include "SDL2_ttf/SDL_ttf.h"

typedef struct		s_drawcmd
{
	int					type;
	char				*name;
	int					draw;
	int					fromx;
	int					fromy;
	int					tox;
	int					toy;
	int					x;
	int					y;
	int					visited;
	int					level;
	int					flashed;
	char				*str;
	int					color_r;
	int					color_g;
	int					color_b;
	int					color_a;
	int					flow;
	int					oflow;
	struct s_drawcmd	*next;
	struct s_drawcmd	*prev;
}						t_drawcmd;

typedef struct			s_visu
{
	int					room_amount;
	int					link_amount;
	int					drawxspaths;
	int					drawxcmds;
	int					drawxedges;
	TTF_Font			*sdl_font;
	SDL_Event			sdl_event;
	SDL_Window			*sdl_window;
	SDL_Renderer		*sdl_renderer;
	int					state;
	t_drawcmd			*cmds;
	t_drawcmd			*drawcmd_head;
}						t_visu;

int					draw_nodes(t_visu *visu);
int					draw_lines(t_visu *visu);
int					draw_nodetexts(t_visu *visu, t_drawcmd *cmd);
int					draw_cmds(t_visu *visu);
char				*draw_cmd_edge(char *line, t_drawcmd *cmd);
char				*draw_cmd_path(char *line, t_drawcmd *cmd);
char				*draw_cmd_fpath(char *line, t_drawcmd *cmd);
char				*draw_cmd_nodes(char *line, t_drawcmd *cmd);
char				*add_cmd(char *line, t_visu *visu, const int type);
t_visu				*init_visu_data(int fd);
int					sn(char *str);
int					between_pipes(char *str);

#endif