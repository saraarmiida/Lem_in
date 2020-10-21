#include "includes/visu.h"

int	draw_nodes(SDL_Renderer *renderer, t_visu *visu)
{
	int i;

	i = 0;
	while (i < visu->room_amount)
	{
		SDL_Rect rect;
		rect.x = visu->nodes[i].x;
		rect.y = visu->nodes[i].y;
		rect.w = NODESIZE;
		rect.h = NODESIZE;
		SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 55, 255, 255, 120);
		SDL_RenderDrawRect(renderer, &rect);
		//SDL_Delay(5);
		//SDL_Delay(5);
		//ft_printf("Node name: %d | x: %d | y: %d\n", visu->nodes[i].name, visu->nodes[i].x, visu->nodes[i].y);
		//ft_printf("Line | from x: %d | from y: %d | to x: %d | to y: %d\n", visu->pathlines[i].fromx, visu->pathlines[i].fromy, visu->pathlines[i].tox, visu->pathlines[i].toy);
		i++;
	}
	return (0);
}