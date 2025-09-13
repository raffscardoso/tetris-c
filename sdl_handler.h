#ifndef SDL_HANDLER_H
#define SDL_HANDLER_H

#include "SDL2/SDL.h"
#include "game.h"

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
} SDL_Handler;

int init_sdl(SDL_Handler *sdl_handler);
void render(SDL_Handler *sdl_handler, GameState *game);
void cleanup_sdl(SDL_Handler *sdl_handler);

#endif // SDL_HANDLER_H
