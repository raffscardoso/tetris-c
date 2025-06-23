#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "create_object.h"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

int main(int argc, char *argv[])
{ 
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    return EXIT_FAILURE;
  }


  SDL_Window* window = SDL_CreateWindow("tetris", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED , SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (!window){
    printf("Window creation error! SDL_Error: %s\n", SDL_GetError() );
    SDL_Quit();
    return EXIT_FAILURE;
  }


  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
  if(!renderer){
    printf("Renderer creation failed! SDL_Error: %s\n", SDL_GetError() );
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_FAILURE;
  }

  SDL_Event e;
  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    create_rectangle(renderer);

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
