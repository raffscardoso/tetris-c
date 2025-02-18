#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include "create_window.h"


// How to compile: gcc main.c create_window.c -lSDL2 -lSDL2main -o main.out
int main(int argc, char *args[]) {
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;

  create_window(window,renderer);

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
