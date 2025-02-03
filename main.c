#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// How to compile: gcc main.c -lSDL2 -lSDL2main -o main.out
int main(int argc, char *args[])
{
  SDL_Window* window = NULL;
  SDL_Surface* surface = NULL; 

  if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
    printf("SDL could not initialize,SDL_Error: %s\n",SDL_GetError());
    
  } else {
    window = SDL_CreateWindow("tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if(window == NULL){
      printf("Error during window creation,SDL_ERROR: %s\n",SDL_GetError());
    } else {
      int keep_window_open = 1;
      while(keep_window_open){
         SDL_Event e;
         while(SDL_PollEvent(&e) > 0){
          switch(e.type)
        {
            case SDL_QUIT:
                keep_window_open = 0;
                break;
        }

        SDL_UpdateWindowSurface(window);
      }
     }
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
