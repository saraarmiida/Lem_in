#include "includes/visu.h"

int			sn(char *str)
{
	int		i;

	i = 0;
	while (ft_isdigit(*str) == 1)
	{
		str++;
		i++;
	}
	while (ft_isdigit(*str) == 0)
	{
		str++;
		i++;
	}
	return (i);
}

static int	drawvisu(t_visu *visu)
{
	draw_cmds(visu);
	SDL_RenderPresent(visu->sdl_renderer);
	return (0);
}

static int	main_loop(t_visu *visu)
{
	SDL_Event e;

	SDL_SetRenderDrawColor(visu->sdl_renderer, 0, 0, 0, 255);
	SDL_RenderClear(visu->sdl_renderer);
	drawvisu(visu);
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			visu->state = -1;
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_SPACE)
				visu->drawxcmds++;
			if (e.key.keysym.sym == SDLK_BACKSPACE)
				visu->drawxcmds--;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
			visu->state = -1;
	}
	SDL_Delay(5);
	return (0);
}

int			main(int argc, char **argv)
{
	t_visu	*visu;
	int		fd;

	fd = 0;
	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	visu = NULL;
	visu = init_visu_data(fd);
	while (visu->state == 0)
		main_loop(visu);
	SDL_DestroyWindow(visu->sdl_window);
	SDL_DestroyRenderer(visu->sdl_renderer);
	TTF_Quit();
	SDL_Quit();
	return (0);
}
