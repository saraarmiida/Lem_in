#include "includes/visu.h"

// Remember to make all functions static

int skip_to_number(char *str)
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
		//ft_printf("Skipped %c\n", *str);
		str++;
		i++;
	}
	return (i);
} 

int	drawvisu(SDL_Renderer *renderer, t_visu *visu)
{
	draw_lines(renderer, visu);
	draw_nodes(renderer, visu);
	draw_text(renderer, visu);
	SDL_RenderPresent(renderer);
	return (0);
}

t_visu *init_visu_data()
{
	t_visu	*visu;
	char	*line;
	t_edge	*edge;
	t_edge	*prev;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(visu = (t_visu*)malloc(sizeof(t_visu))))
		return (0);
	visu->room_amount = 0;
	visu->head = NULL;
	while (get_next_line(0, &line) == 1)
	{
		if (ft_strncmp(line, "Edge", 3) == 0)
		{
			if (!(edge = (t_edge*)malloc(sizeof(t_edge))))
				return (0);
			edge->fromx = ft_atoi(line += skip_to_number(line)) * PADDING + OFFSETX + NODESIZE / 2; 
			edge->fromy = ft_atoi(line += skip_to_number(line)) * PADDING + OFFSETY + NODESIZE / 2;
			edge->tox = ft_atoi(line += skip_to_number(line)) * PADDING + OFFSETX + NODESIZE / 2; 
			edge->toy = ft_atoi(line += skip_to_number(line)) * PADDING + OFFSETY + NODESIZE / 2;
			if (edge->fromx > edge->tox)
			{
				edge->tox += (edge->fromx - edge->tox) / 2;
			}
			else if (edge->fromx < edge->tox)
			{
				edge->tox -= (edge->tox - edge->fromx) / 2;
			}
			if (edge->fromy > edge->toy)
			{
				edge->toy += (edge->fromy - edge->toy) / 2;
			}
			else if (edge->fromy < edge->toy)
			{
				edge->toy -= (edge->toy - edge->fromy) / 2;
			}
			edge->next = NULL;
			ft_putstr_fd("Added edge", 2);
			if (visu->head == NULL)
				visu->head = edge;
			else
				prev->next = edge;
			prev = edge;
		}
		if (ft_strncmp(line, "Rooms", 4) == 0 && visu->room_amount == 0)
		{
			visu->room_amount = ft_atoi(line += 6);
			visu->link_amount = ft_atoi(line += 8 + ft_intlen(visu->room_amount));
			if (!(visu->nodes = (t_node*)malloc(sizeof(t_node) * visu->room_amount)))
			{
				ft_putstr_fd("Failed to malloc rooms.\n", 2);
				return (0);
			}
			ft_putstr_fd("Malloced rooms.\n", 2);
			if (!(visu->pathlines = (t_line*)malloc(sizeof(t_line) * visu->link_amount)))
			{
				ft_putstr_fd("Failed to malloc used paths.\n", 2);
				return (0);
			}
			ft_putstr_fd("Malloced used paths.\n", 2);
			if (!(visu->lines = (t_line*)malloc(sizeof(t_line) * visu->link_amount * 2)))
			{
				ft_putstr_fd("Failed to malloc all paths.\n", 2);
				return (0);
			}
			ft_putstr_fd("Malloced all paths.\n", 2);
		}
		if (ft_strncmp(line, "Name", 3) == 0)
		{
			visu->nodes[i].name = ft_atoi(line += skip_to_number(line));
			visu->nodes[i].x = ft_atoi(line += skip_to_number(line)) * PADDING + OFFSETX;
			visu->nodes[i].y = ft_atoi(line += skip_to_number(line)) * PADDING + OFFSETY;
			visu->nodes[i].level = ft_atoi(line += skip_to_number(line));
			i++;
		}
		if (ft_strncmp(line, "Curr", 3) == 0)
		{
			visu->pathlines[j].fromx = ft_atoi(line += skip_to_number(line)) * PADDING + OFFSETX + NODESIZE / 2; 
			visu->pathlines[j].fromy = ft_atoi(line += skip_to_number(line)) * PADDING + OFFSETY + NODESIZE / 2;
			visu->pathlines[j].tox = ft_atoi(line += skip_to_number(line)) * PADDING + OFFSETX + NODESIZE / 2; 
			visu->pathlines[j].toy = ft_atoi(line += skip_to_number(line)) * PADDING + OFFSETY + NODESIZE / 2;
			j++;
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

	SDL_Window *win =  SDL_CreateWindow("Henlo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 700, SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_Renderer *renderer = NULL;
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	SDL_Event e;
	int quit = 0;
	if (!win)
	{
		printf("No window: %s", SDL_GetError());
		return (0);
	}
	visu = init_visu_data();
	TTF_Init();
	visu->font = TTF_OpenFont("../assets/OverpassMono-Light.ttf", 12);
	linesmax = visu->link_amount;
	visu->drawxpaths = 0;
	visu->drawxedges = 0;
	while (quit == 0){
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		drawvisu(renderer, visu);
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
				quit = 1;
			}
			if (e.type == SDL_KEYDOWN){
				switch( e.key.keysym.sym ){
                    case SDLK_RIGHT:
                        visu->drawxpaths++;
                        break;
                    case SDLK_UP:
                        visu->drawxedges++;
                        break;
                    default:
                        break;
                }
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