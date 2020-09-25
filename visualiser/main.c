#include "../includes/lem_in.h"
#include "includes/SDL.h"
#include <stdio.h>

typedef struct	s_node
{
	int			x;
	int			y;
	int			name;
}				t_node;

int	drawnodes(SDL_Renderer *renderer, t_node *nodes)
{
	int i;

	i = 0;
	while (i < 9)
	{
		SDL_Rect rect;
		rect.x = nodes[i].x;
		rect.y = nodes[i].y;
		rect.w = 10;
		rect.h = 10;
		SDL_SetRenderDrawColor(renderer, 55, 255, 255, 255);
		SDL_Delay(10);
		SDL_RenderDrawRect(renderer, &rect);
		SDL_Delay(10);
		SDL_RenderPresent(renderer);
		SDL_Delay(10);
		ft_printf("Node name: %d | x: %d | y: %d\n", nodes[i].name, nodes[i].x, nodes[i].y);
		i++;
	}
	return (0);
}

t_node *read_lem_in()
{
	char 	*line;
	t_node 	*nodes;
	int		x;
	int		y;
	int		content;
	int		i;

	x = 0;
	y = 0;
	content = 0;
	i = 0;
	if (!(nodes = (t_node*)malloc(sizeof(t_node) * 8)))
		return (0);
	while (get_next_line(0, &line) == 1)
	{
		if (ft_strncmp(line, "Name", 3) == 0)
		{
			nodes[i].name = ft_atoi(line += 5);
			nodes[i].x = ft_atoi(line += 7) * 10 + 550;
			nodes[i].y = ft_atoi(line += 7) * 10 + 100;
			i++;
		}
	}
	return (nodes);
}

int main() {
	t_node 	*nodes;

	nodes = NULL;
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
	nodes = read_lem_in();
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
		drawnodes(renderer, nodes);
		//SDL_Delay(100);
	}
	printf("There was a window supposedly.\n");
	SDL_DestroyWindow(win);
	SDL_Quit();
	return (0);
}