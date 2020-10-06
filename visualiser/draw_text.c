#include "includes/visu.h"

int	draw_text(SDL_Renderer *renderer, t_visu *visu)
{
	TTF_Font	*Mono;
	Mono = TTF_OpenFont("../assets/OverpassMono-Light.ttf", 10);
	SDL_Color White = {255, 255, 255, 255}; 
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Mono, "Hello world", White);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); 
	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 100;  //controls the rect's x coordinate 
	Message_rect.y = 100; // controls the rect's y coordinte
	Message_rect.w = surfaceMessage->w; // controls the width of the rect
	Message_rect.h = surfaceMessage->h;; // controls the height of the rect
	ft_putnbr_fd(visu->room_amount, 2);

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
	return (0);
}