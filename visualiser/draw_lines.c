#include "includes/visu.h"

int	draw_lines(SDL_Renderer *renderer, t_visu *visu)
{
	int i;
	i = 0;

	while (i < visu->link_amount)
	{
		//ft_printf("Line | from x: %d | from y: %d | to x: %d | to y: %d\n", visu->lines[i].fromx, visu->lines[i].fromy, visu->lines[i].tox, visu->lines[i].toy);
		SDL_SetRenderDrawColor(renderer, 55, 255, 255, 255);
		SDL_RenderDrawLine(renderer, visu->lines[i].fromx, visu->lines[i].fromy, visu->lines[i].tox, visu->lines[i].toy);
		//SDL_Delay(5);
		i++;
	}
	return (0);
}