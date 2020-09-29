#include "../includes/lem_in.h"
#include "includes/SDL.h"
#include <stdio.h>


typedef struct	s_node
{
	int			x;
	int			y;
	int			name;
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
}				t_visu;

int	drawvisu(SDL_Renderer *renderer, t_visu *visu)
{
	int i;
	int j;

	i = 0;
	while (i < 8)
	{
		SDL_Rect rect;
		rect.x = visu->nodes[i].x;
		rect.y = visu->nodes[i].y;
		rect.w = 10;
		rect.h = 10;
		SDL_SetRenderDrawColor(renderer, 55, 255, 255, 255);
		SDL_Delay(5);
		SDL_RenderDrawRect(renderer, &rect);
		SDL_Delay(5);
		SDL_RenderPresent(renderer);
		SDL_Delay(5);
		//ft_printf("Node name: %d | x: %d | y: %d\n", visu->nodes[i].name, visu->nodes[i].x, visu->nodes[i].y);
		//ft_printf("Line | from x: %d | from y: %d | to x: %d | to y: %d\n", visu->lines[i].fromx, visu->lines[i].fromy, visu->lines[i].tox, visu->lines[i].toy);
		j = 0;
		while (j < 8)
		{
			ft_printf("Line | from x: %d | from y: %d | to x: %d | to y: %d\n", visu->lines[j].fromx, visu->lines[j].fromy, visu->lines[j].tox, visu->lines[j].toy);
			SDL_RenderDrawLine(renderer, visu->lines[j].fromx, visu->lines[j].fromy, visu->lines[j].tox, visu->lines[j].toy);
			SDL_Delay(1);
			j++;
		}
		i++;
	}
	return (0);
}

t_visu *init_visu_data()
{
	t_visu	*visu;
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(visu = (t_visu*)malloc(sizeof(t_visu))))
		return (0);
	if (!(visu->nodes = (t_node*)malloc(sizeof(t_node) * 8)))
		return (0);
	if (!(visu->lines = (t_line*)malloc(sizeof(t_line) * 8)))
		return (0);
	while (get_next_line(0, &line) == 1)
	{
		if (ft_strncmp(line, "Curr", 3) == 0)
		{
			visu->lines[j].fromx = ft_atoi(line += 5) * 10 + 550; 
			visu->lines[j].fromy = ft_atoi(line += 4) * 10 + 100;
			visu->lines[j].tox = ft_atoi(line += 4) * 10 + 550; 
			visu->lines[j].toy = ft_atoi(line += 4) * 10 + 100;
			j++;
		}
		if (ft_strncmp(line, "Name", 3) == 0)
		{
			visu->nodes[i].name = ft_atoi(line += 5);
			visu->nodes[i].x = ft_atoi(line += 7) * 10 + 550;
			visu->nodes[i].y = ft_atoi(line += 7) * 10 + 100;
			i++;
		}
	}
	return(visu);
}

int main() {
	t_visu 	*visu;

	visu = NULL;
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
	visu = init_visu_data();
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
		drawvisu(renderer, visu);
		//SDL_Delay(100);
	}
	printf("There was a window supposedly.\n");
	SDL_DestroyWindow(win);
	SDL_Quit();
	return (0);
}