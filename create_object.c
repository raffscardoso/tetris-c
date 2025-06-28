#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include "create_object.h"


void create_rectangle(SDL_Renderer* renderer, int width, int height, int x, int y){
  SDL_Rect rect;
  rect.w = width;
  rect.h = height;
  rect.x = x;
  rect.y = y;

  SDL_SetRenderDrawColor(renderer, 255,255,255, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(renderer, &rect);
}



