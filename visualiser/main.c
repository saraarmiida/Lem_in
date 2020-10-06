#include "../includes/lem_in.h"
#include <stdio.h>


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
}				t_visu;

int	drawvisu(SDL_Renderer *renderer, t_visu *visu)
{
	int i;
	int j;
	TTF_Font	*Mono;

	i = 0;
	j = 0;
	while (i < visu->room_amount)
	{
		SDL_Rect rect;
		rect.x = visu->nodes[i].x;
		rect.y = visu->nodes[i].y;
		rect.w = 10;
		rect.h = 10;
		SDL_SetRenderDrawColor(renderer, 55, 255, 255, 255);
		//SDL_Delay(5);
		SDL_RenderDrawRect(renderer, &rect);
		//SDL_Delay(5);
		//ft_printf("Node name: %d | x: %d | y: %d\n", visu->nodes[i].name, visu->nodes[i].x, visu->nodes[i].y);
		//ft_printf("Line | from x: %d | from y: %d | to x: %d | to y: %d\n", visu->lines[i].fromx, visu->lines[i].fromy, visu->lines[i].tox, visu->lines[i].toy);
		i++;
	}
	while (j < visu->link_amount)
	{
		//ft_printf("Line | from x: %d | from y: %d | to x: %d | to y: %d\n", visu->lines[j].fromx, visu->lines[j].fromy, visu->lines[j].tox, visu->lines[j].toy);
		SDL_SetRenderDrawColor(renderer, 55, 255, 255, 255);
		SDL_RenderDrawLine(renderer, visu->lines[j].fromx, visu->lines[j].fromy, visu->lines[j].tox, visu->lines[j].toy);
		//SDL_Delay(5);
		j++;
	}

	TTF_Init();
	Mono = TTF_OpenFont("../assets/OverpassMono-Light.ttf", 24);
	SDL_Color White = {255, 255, 255, 255}; 
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Mono, "Hello world", White);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); 
	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 0;  //controls the rect's x coordinate 
	Message_rect.y = 0; // controls the rect's y coordinte
	Message_rect.w = 300; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
	SDL_RenderPresent(renderer);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
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
	visu->room_amount = 0;
	while (get_next_line(0, &line) == 1)
	{
		if (ft_strncmp(line, "Rooms", 4) == 0 && visu->room_amount == 0)
		{
			visu->room_amount = ft_atoi(line += 6);
			visu->link_amount = ft_atoi(line += 9);
			if (!(visu->nodes = (t_node*)malloc(sizeof(t_node) * visu->room_amount)))
				return (0);
			if (!(visu->lines = (t_line*)malloc(sizeof(t_line) * visu->link_amount)))
				return (0);
		}
		if (ft_strncmp(line, "Curr", 3) == 0)
		{
			visu->lines[j].fromx = ft_atoi(line += 5) * 10 + 555; 
			visu->lines[j].fromy = ft_atoi(line += 4) * 10 + 105;
			visu->lines[j].tox = ft_atoi(line += 4) * 10 + 555; 
			visu->lines[j].toy = ft_atoi(line += 4) * 10 + 105;
			j++;
		}
		if (ft_strncmp(line, "Name", 3) == 0)
		{
			visu->nodes[i].name = ft_atoi(line += 5);
			visu->nodes[i].x = ft_atoi(line += 7) * 10 + 550;
			visu->nodes[i].y = ft_atoi(line += 7) * 10 + 100;
			visu->nodes[i].level = ft_atoi(line += 7);
			i++;
		}
	}
	return(visu);
}

int main() {
	t_visu 		*visu;
	int			linesmax;
	
	visu = NULL;
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
	{
		printf("NO SDL\n");
		return (1);
	}

	SDL_Window *win =  SDL_CreateWindow("Henlo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 700, 0);
	SDL_Renderer *renderer = NULL;
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	SDL_Event e;
	int quit = 0;
	if (!win)
	{
		printf("No window: %s", SDL_GetError());
		return (0);
	}
	visu = init_visu_data();
	linesmax = visu->link_amount;
	visu->link_amount = 0;
	while (quit == 0){
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		drawvisu(renderer, visu);
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
				quit = 1;
			}
			if (e.type == SDL_KEYDOWN && visu->link_amount <= linesmax){
				visu->link_amount++;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN){
				quit = 1;
			}
		}
		SDL_Delay(5);
	}
	printf("There was a window supposedly.\n");
	SDL_DestroyWindow(win);
	SDL_Quit();
	return (0);
}