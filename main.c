#include <stdio.h>
#include <SDL2/SDL.h>


// How to compile: gcc main.c -lSDL2 -lSDL2main -o main.out
int main(int argc, char *argv[])
{
  SDL_Init(SDL_INIT_VIDEO);  
  if (SDL_Init != 0){
    printf("Error in initialization!");
    return 1;
  }
}
