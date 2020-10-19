#include "includes/visu.h"

int	draw_lines(SDL_Renderer *renderer, t_visu *visu)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < visu->link_amount)
	{
		SDL_SetRenderDrawColor(renderer, 55, 55, 55, 255);
		SDL_RenderDrawLine(renderer, visu->lines[i].fromx, visu->lines[i].fromy, visu->lines[i].tox, visu->lines[i].toy);
		//SDL_Delay(5);
		i++;
	}
	while (j < visu->drawxlinks)
	{
		ft_printf("Line | from x: %d | from y: %d | to x: %d | to y: %d\n", visu->pathlines[j].fromx, visu->pathlines[j].fromy, visu->pathlines[j].tox, visu->pathlines[j].toy);
		SDL_SetRenderDrawColor(renderer, 55, 255, 255, 255);
		SDL_RenderDrawLine(renderer, visu->pathlines[j].fromx, visu->pathlines[j].fromy, visu->pathlines[j].tox, visu->pathlines[j].toy);
		//SDL_Delay(5);
		j++;
	}
	return (0);
}