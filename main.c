#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

#define COLS 10
#define ROWS 20
const int BLOCK_SIZE = 32; // 32x32 pixels for each block
const int WINDOW_WIDTH = COLS * BLOCK_SIZE;
const int WINDOW_HEIGHT = ROWS * BLOCK_SIZE;

 typedef struct{
  int x,y;
  int shape[4][4];
} Tetromino;

int main(int argc, char *argv[]) { 

  // Initializing SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0){
    printf("Error on initializing SDL: %s\n", SDL_GetError());
    return 1;
  }

  // Creating a window
  SDL_Window* window = SDL_CreateWindow(
    "Tetris",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    SDL_WINDOW_SHOWN
  );

  if(window == NULL){
    printf("Error on window creation: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }


  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if(renderer == NULL){
    printf("Erro ao criar o renderer: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  int grid[ROWS][COLS] = {0};
  
  Tetromino pieces[7] = {
    {0, 0,
      { // piece I
      {0,1,0,0},
      {0,1,0,0},
      {0,1,0,0},
      {0,1,0,0},
    }}, 
    { 0, 0, 
      { // piece J
      {1,1,1,1},
      {1,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    }}, 
    {0,0,
      { // piece L
      {0,0,0,1},
      {0,1,1,1},
      {0,0,0,0},
      {0,0,0,0}
    }},
    {0,0,  
      { // piece O
      {0,1,1,0},
      {0,1,1,0},
      {0,0,0,0},
      {0,0,0,0}
    }},
    {0,0,
      { // piece S
      {0,0,1,1},
      {0,1,1,0},
      {0,0,0,0},
      {0,0,0,0}
    }},
    {0,0,
      { // piece T
      {0,1,0,0},
      {1,1,1,0},
      {0,0,0,0},
      {0,0,0,0}
    }},
    {0,0,
      { // piece Z
      {1,1,0,0},
      {0,1,1,0},
      {0,0,0,0},
      {0,0,0,0}
    }}
  };

  Tetromino actual_piece = pieces[3];
  actual_piece.x = 3; // initial position: col 3
  actual_piece.y = 0; // initial position: row 0 (top)


  Uint32 last_fall_time = 0;
  const int gravity_delay = 500; // the tetromino will fall every 500ms
  

  int running = 1;
  SDL_Event event;

  while(running){
    while(SDL_PollEvent(&event)){
      if (event.type == SDL_QUIT) {
        running = 0;
      }
    }



    Uint32 actual_time = SDL_GetTicks();
    if(actual_time > last_fall_time + gravity_delay){ // gravity logic
      actual_piece.y++;
      last_fall_time = actual_time;
    }

      
    // Clear the window with background color (light gray)
    SDL_SetRenderDrawColor(renderer, 30,30,30,255);
    SDL_RenderClear(renderer);

    // Draw the grid
    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255); 
    for (int i = 0; i < ROWS; i++) {
      for(int j = 0; j < COLS; j++){
        SDL_Rect rect = {j * BLOCK_SIZE, i * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
        SDL_RenderDrawRect(renderer, &rect);
      } 
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

    for(int i = 0; i < 4; i++){
      for(int j = 0; j < 4; j++){
        if(actual_piece.shape[i][j] == 1){
          SDL_Rect piece_block = {
            (actual_piece.x + j ) * BLOCK_SIZE,
            (actual_piece.y + i ) * BLOCK_SIZE,
            BLOCK_SIZE,
            BLOCK_SIZE
          };

          SDL_RenderFillRect(renderer,&piece_block);
        }
      }
    }


    // Displays the drawing
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0; 
}
