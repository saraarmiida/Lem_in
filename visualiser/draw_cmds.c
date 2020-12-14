#include "includes/visu.h"

int					render_node(t_visu *visu, t_drawcmd *cmd)
{
	SDL_Rect		rect;

	rect.x = cmd->x;
	rect.y = cmd->y;
	rect.w = NODESIZE;
	rect.h = NODESIZE;
	if (cmd->flashed == 0)
	{
		SDL_SetRenderDrawColor(visu->sdl_renderer, 255, 255, 0, 255);
		SDL_RenderFillRect(visu->sdl_renderer, &rect);
		SDL_RenderPresent(visu->sdl_renderer);
		SDL_Delay(30);
		cmd->flashed = 1;
	}
	SDL_SetRenderDrawColor(visu->sdl_renderer, 40, 40, 40, 255);
	SDL_RenderFillRect(visu->sdl_renderer, &rect);
	SDL_SetRenderDrawColor(visu->sdl_renderer, 55, 255, 255, 80);
	SDL_RenderDrawRect(visu->sdl_renderer, &rect);
	draw_nodetexts(visu, cmd);
	return (0);
}

char				*add_cmd(char *line, t_visu *visu, const int type)
{
	t_drawcmd		*cmd;

	cmd = NULL;
	if (!(cmd = (t_drawcmd*)malloc(sizeof(t_drawcmd))))
		return (NULL);
	if (type == DRAW_EDGE)
		line = draw_cmd_edge(line, cmd);
	if (type == DRAW_PATH)
		line = draw_cmd_path(line, cmd);
	if (type == DRAW_NODE)
		line = draw_cmd_nodes(line, cmd);
	if (type == DRAW_FPTH)
		line = draw_cmd_fpath(line, cmd);
	if (visu->drawcmd_head == NULL)
	{
		visu->drawcmd_head = cmd;
		visu->cmds = cmd;
	}
	else
	{
		visu->cmds->next = cmd;
		visu->cmds = visu->cmds->next;
	}
	return (line);
}

int					draw_cmds(t_visu *visu)
{
	t_drawcmd		*cmd;
	int				i;

	i = 0;
	cmd = visu->drawcmd_head;
	while (cmd != NULL && i < visu->drawxcmds)
	{
		SDL_SetRenderDrawColor(visu->sdl_renderer, cmd->color_r,
		cmd->color_g, cmd->color_b, cmd->color_a);
		if ((cmd->type == DRAW_EDGE || cmd->type == DRAW_PATH ||
		cmd->type == DRAW_FPTH) && cmd->draw == 1)
			SDL_RenderDrawLine(visu->sdl_renderer, cmd->fromx,
			cmd->fromy, cmd->tox, cmd->toy);
		else if (cmd->type == DRAW_NODE && cmd->draw == 1)
			render_node(visu, cmd);
		cmd = cmd->next;
		i++;
	}
	return (0);
}

int					draw_nodetexts(t_visu *visu, t_drawcmd *cmd)
{
	char			*debug;
	SDL_Color		white;
	SDL_Surface		*surfacemessage;
	SDL_Texture		*message;
	SDL_Rect		message_rect;

	white.r = 255;
	white.g = 255;
	white.b = 255;
	white.a = 255;
	debug = ft_itoa(cmd->level);
	surfacemessage = TTF_RenderText_Blended(visu->sdl_font, debug, white);
	message = SDL_CreateTextureFromSurface(visu->sdl_renderer, surfacemessage);
	message_rect.x = cmd->x + NODESIZE / 2 - surfacemessage->w / 2;
	message_rect.y = cmd->y + NODESIZE / 6;
	message_rect.w = surfacemessage->w;
	message_rect.h = surfacemessage->h;
	ft_strdel(&debug);
	SDL_RenderCopy(visu->sdl_renderer, message, NULL, &message_rect);
	SDL_FreeSurface(surfacemessage);
	SDL_DestroyTexture(message);
	return (0);
}
