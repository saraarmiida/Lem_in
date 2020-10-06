#include "includes/visu.h"

int	draw_text(SDL_Renderer *renderer, t_visu *visu)
{
	TTF_Font	*Mono;
	TTF_Init();
	Mono = TTF_OpenFont("../assets/OverpassMono-Light.ttf", 8);
	SDL_Color White = {255, 255, 255, 255}; 
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Mono, ft_itoa(visu->room_amount), White);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); 
	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 0;  //controls the rect's x coordinate 
	Message_rect.y = 0; // controls the rect's y coordinte
	Message_rect.w = 300; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
	return (0);
}