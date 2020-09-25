#include "../includes/lem_in.h"
#include "includes/SDL.h"
#include <stdio.h>

int	drawnode(SDL_Renderer *renderer, int x, int y, int content)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = 10;
	rect.h = 10;
	content++;
	SDL_SetRenderDrawColor(renderer, 55, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &rect);
	SDL_RenderPresent(renderer);
	return (0);
}

int read_lem_in(SDL_Renderer *renderer)
{
	char 	*line;
	int		x;
	int		y;
	int		content;

	x = 0;
	y = 0;
	content = 0;
	while (get_next_line(0, &line) == 1)
	{
		if (ft_strncmp(line, "Name", 3) == 0)
		{
			content = ft_atoi(line += 5);
			x = ft_atoi(line += 7);
			y = ft_atoi(line += 7);
			x *= 10;
			y *= 10;
			x += 550;
			y += 100;
			ft_printf("Node content: %d | x: %d | y: %d\n", content, x, y);
			drawnode(renderer, x, y, content);
			SDL_Delay(1000);
		}
	}
	return (0);
}

int main() {
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
	{
		printf("NO SDL\n");
		return (1);
	}
	SDL_Window *win =  SDL_CreateWindow("Henlo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 700, 0);
	SDL_Renderer *renderer = NULL;
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderClear(renderer);
	SDL_Event e;
	int quit = 0;
	if (!win)
	{
		printf("No window: %s", SDL_GetError());
		return (0);
	}
	while (quit == 0){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
				quit = 1;
			}
			if (e.type == SDL_KEYDOWN){
				quit = 1;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN){
				quit = 1;
			}
		}
		read_lem_in(renderer);
	}
	printf("There was a window supposedly.\n");
	SDL_DestroyWindow(win);
	SDL_Quit();
	return (0);
}