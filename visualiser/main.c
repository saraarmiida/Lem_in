#include "../includes/lem_in.h"
#include "includes/SDL.h"
#include <stdio.h>

int read_lem_in()
{
	char *line;

	while (get_next_line(0, &line) == 1)
	{
		if (ft_strncmp(line, "Name", 3) == 0)
		{
			ft_printf("%s\n", line);
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
	SDL_Window *win =  SDL_CreateWindow("Henlo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
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
		read_lem_in();
	}
	printf("There was a window supposedly.\n");
	SDL_DestroyWindow(win);
	SDL_Quit();
	return (0);
}