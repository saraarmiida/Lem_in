/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:03:23 by tlouekar          #+#    #+#             */
/*   Updated: 2020/12/27 11:37:00 by tlouekar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/visu.h"

static char	*init_rooms_links(char *line, t_visu *visu)
{
	if (ft_strncmp(line, "#Rooms", 5) == 0 && visu->room_amount == 0)
		visu->room_amount = ft_atoi(line += sn(line));
	if (ft_strncmp(line, "#Links", 5) == 0)
		visu->link_amount = ft_atoi(line += sn(line));
	return (line);
}

static char	*init_drawcmds(char *line, t_visu *visu)
{
	if (ft_strncmp(line, "#e|", 3) == 0)
		line = add_cmd(line, visu, DRAW_EDGE);
	if (ft_strncmp(line, "#n|", 3) == 0)
		line = add_cmd(line, visu, DRAW_NODE);
	if (ft_strncmp(line, "#s|", 3) == 0)
		line = add_cmd(line, visu, DRAW_PATH);
	if (ft_strncmp(line, "#f|", 3) == 0)
		line = add_cmd(line, visu, DRAW_FPTH);
	return (line);
}

static int	init_sdl(t_visu *visu)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		printf("NO SDL\n");
		return (-1);
	}
	visu->sdl_window = SDL_CreateWindow("Henlo", SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, 1200, 700, SDL_WINDOW_ALLOW_HIGHDPI);
	visu->sdl_renderer = SDL_CreateRenderer(visu->sdl_window, -1,
	SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(visu->sdl_renderer, SDL_BLENDMODE_BLEND);
	if (!visu->sdl_window)
	{
		printf("No window: %s", SDL_GetError());
		return (-1);
	}
	TTF_Init();
	visu->sdl_font = TTF_OpenFont("./assets/OverpassMono-Light.ttf", FONTSIZE);
	return (0);
}

t_visu		*init_visu_data(int fd)
{
	t_visu	*visu;
	char	*line;
	char	*temp;

	if (!(visu = (t_visu*)malloc(sizeof(t_visu))))
		return (0);
	visu->room_amount = 0;
	visu->link_amount = 0;
	visu->drawxcmds = 0;
	visu->state = 0;
	visu->cmds = NULL;
	visu->drawcmd_head = NULL;
	while (get_next_line(fd, &line) == 1)
	{
		temp = line;
		temp = init_rooms_links(temp, visu);
		temp = init_drawcmds(temp, visu);
		ft_strdel(&line);
	}
	init_sdl(visu);
	return (visu);
}
