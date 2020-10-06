#include "includes/visu.h"

int	draw_text(SDL_Renderer *renderer, t_visu *visu)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	SDL_Color White = {255, 255, 255, 255}; 
	while (i < visu->room_amount)
	{
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(visu->font, ft_itoa(visu->nodes[i].name), White);
		SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); 
		SDL_Rect Message_rect; //create a rect
		Message_rect.x = visu->nodes[i].x - 10;  //controls the rect's x coordinate 
		Message_rect.y = visu->nodes[i].y - 2; // controls the rect's y coordinte
		Message_rect.w = surfaceMessage->w; // controls the width of the rect
		Message_rect.h = surfaceMessage->h; // controls the height of the rect
		SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(Message);
		i++;
	}
	while (j < visu->link_amount)
	{
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(visu->font, ft_itoa(visu->lines[j].fromx), White);
		SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); 
		SDL_Rect Message_rect; //create a rect
		Message_rect.x = visu->lines[j].fromx - 10;  //controls the rect's x coordinate 
		Message_rect.y = visu->lines[j].fromy - 2; // controls the rect's y coordinte
		Message_rect.w = surfaceMessage->w; // controls the width of the rect
		Message_rect.h = surfaceMessage->h; // controls the height of the rect
		SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(Message);
		j++;
	}
	return (0);
}