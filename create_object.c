#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include "create_object.h"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480


void create_rectangle(SDL_Renderer* renderer){
  SDL_Rect rect;
  rect.w = 50;
  rect.h = 50;
  rect.x = (SCREEN_WIDTH - rect.w) / 2;
  rect.y = (SCREEN_HEIGHT - rect.h) / 2;

  SDL_SetRenderDrawColor(renderer, 255,255,255, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(renderer, &rect);
}



