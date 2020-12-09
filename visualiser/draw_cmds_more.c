#include "includes/visu.h"

char	*draw_cmd_edge(char *line, t_drawcmd *cmd)
{
	cmd->fromx = ft_atoi(line += sn(line)) * PADDING + OFFSETX + NODESIZE / 2;
	cmd->fromy = ft_atoi(line += sn(line)) * PADDING + OFFSETY + NODESIZE / 2;
	cmd->tox = ft_atoi(line += sn(line)) * PADDING + OFFSETX + NODESIZE / 2;
	cmd->toy = ft_atoi(line += sn(line)) * PADDING + OFFSETY + NODESIZE / 2;
	cmd->type = DRAW_EDGE;
	cmd->color_r = 255;
	cmd->color_g = 0;
	cmd->color_b = 255;
	cmd->color_a = 200;
	cmd->next = NULL;
	cmd->draw = 1;
	return (line);
}

char	*draw_cmd_path(char *line, t_drawcmd *cmd)
{
	cmd->fromx = ft_atoi(line += sn(line)) * PADDING + OFFSETX + NODESIZE / 2;
	cmd->fromy = ft_atoi(line += sn(line)) * PADDING + OFFSETY + NODESIZE / 2;
	cmd->tox = ft_atoi(line += sn(line)) * PADDING + OFFSETX + NODESIZE / 2;
	cmd->toy = ft_atoi(line += sn(line)) * PADDING + OFFSETY + NODESIZE / 2;
	cmd->type = DRAW_PATH;
	cmd->color_r = 255;
	cmd->color_g = 255;
	cmd->color_b = 0;
	cmd->color_a = 200;
	cmd->next = NULL;
	cmd->draw = 1;
	return (line);
}

char	*draw_cmd_fpath(char *line, t_drawcmd *cmd)
{
	cmd->fromx = ft_atoi(line += sn(line)) * PADDING + OFFSETX + NODESIZE / 2;
	cmd->fromy = ft_atoi(line += sn(line)) * PADDING + OFFSETY + NODESIZE / 2;
	cmd->tox = ft_atoi(line += sn(line)) * PADDING + OFFSETX + NODESIZE / 2;
	cmd->toy = ft_atoi(line += sn(line)) * PADDING + OFFSETY + NODESIZE / 2;
	cmd->type = DRAW_FPTH;
	cmd->color_r = 0;
	cmd->color_g = 255;
	cmd->color_b = 255;
	cmd->color_a = 200;
	cmd->next = NULL;
	cmd->draw = 1;
	return (line);
}

char	*draw_cmd_nodes(char *line, t_drawcmd *cmd)
{
	cmd->x = ft_atoi(line += sn(line)) * PADDING + OFFSETX;
	cmd->y = ft_atoi(line += sn(line)) * PADDING + OFFSETY;
	cmd->visited = ft_atoi(line += sn(line));
	cmd->level = ft_atoi(line += sn(line));
	line += between_pipes(line);
	cmd->name = ft_strsub(line, 1, between_pipes(line));
	cmd->type = DRAW_NODE;
	cmd->draw = 1;
	cmd->next = NULL;
	cmd->flashed = 0;
	return (line);
}
