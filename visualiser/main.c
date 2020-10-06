#include "includes/visu.h"

int	drawvisu(SDL_Renderer *renderer, t_visu *visu)
{
	draw_nodes(renderer, visu);
	draw_lines(renderer, visu);
	draw_text(renderer, visu);
	SDL_RenderPresent(renderer);
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

int main()
{
	t_visu 		*visu;
	int			linesmax;
	
	visu = NULL;
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
	{
		printf("NO SDL\n");
		return (1);
	}

	TTF_Init();
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
	TTF_Quit();
	SDL_Quit();
	return (0);
}