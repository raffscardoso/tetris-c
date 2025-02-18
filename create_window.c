#include "create_window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void create_rect(SDL_Renderer *renderer){
  SDL_Rect *rect;
  rect->x = 270;
  rect->y = 10;
  rect->w = 100;
  rect->h = 20;
  
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderDrawRect(renderer,rect);
  SDL_RenderFillRect(renderer, rect);
}

void create_window(SDL_Window *window, SDL_Renderer *renderer){

  if (SDL_Init(SDL_INIT_EVERYTHING)) {
      printf("SDL could not initialize,SDL_Error: %s\n", SDL_GetError());
    } else {
      window = SDL_CreateWindow("tetris", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
      renderer = SDL_CreateRenderer(window, -1 , 0);
      
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);


      create_rect(renderer);
      SDL_RenderPresent(renderer);
      

      if (window == NULL) {
        printf("Error during window creation,SDL_ERROR: %s\n", SDL_GetError());
      } else {
        int keep_window_open = 1;
        while (keep_window_open) {
          SDL_Event e;

          while (SDL_PollEvent(&e) > 0) {
            switch (e.type) {
            case SDL_QUIT:
              keep_window_open = 0;
              break;
            }
            
            SDL_UpdateWindowSurface(window);
          }
        }
      }
    }
}
