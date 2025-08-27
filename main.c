#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

int main(int argc, char *argv[]) { 

  // Inicializando o SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0){
    printf("Erro ao inicializar o SDL: %s\n", SDL_GetError());
    return 1;
  }

  //Criando uma janela
  SDL_Window* window = SDL_CreateWindow(
    "Tetris",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    640,
    480,
    SDL_WINDOW_SHOWN
  );

  if(window == NULL){
    printf("Erro ao criar janela: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  // Mantem janela aberta por 5 segundos
  SDL_Delay(5000);


  //Destroi janela e finaliza SDL
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0; 
}
