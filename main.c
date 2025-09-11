#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COLS 10
#define ROWS 20

const int BLOCK_SIZE = 32; // 32x32 pixels for each block
const int WINDOW_WIDTH = COLS * BLOCK_SIZE;
const int WINDOW_HEIGHT = ROWS * BLOCK_SIZE;

typedef struct {
  int x, y;
  int shape[4][4];
} Tetromino;

void fix_piece_on_grid(Tetromino piece, int grid[ROWS][COLS]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (piece.shape[i][j] == 1) {
        int pos_x = piece.x + j;
        int pos_y = piece.y + i;

        grid[pos_y][pos_x] = 1;
      }
    }
  }
}

int check_collision(Tetromino piece, int grid[ROWS][COLS]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (piece.shape[i][j] == 1) {
        int pos_x_grid = piece.x + j;
        int pos_y_grid = piece.y + i;

        if (pos_x_grid < 0 || pos_x_grid >= COLS)
          return 1;
        if (pos_y_grid >= ROWS)
          return 1;
        if (pos_y_grid >= 0 && grid[pos_y_grid][pos_x_grid] != 0)
          return 1;
      }
    }
  }
  return 0; // 0 = no collision
}

void set_render_draw_SDL_Color(SDL_Renderer *renderer, SDL_Color *color) {
  SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
}

int main(int argc, char *argv[]) {

  srand(time(NULL));

  // Initializing SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Error on initializing SDL: %s\n", SDL_GetError());
    return 1;
  }

  // Creating a window
  SDL_Window *window =
      SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

  if (window == NULL) {
    printf("Error on window creation: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    printf("Error on renderer creation: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  int grid[ROWS][COLS] = {0};

  Tetromino pieces[7] = {{0,
                          0,
                          {
                              // piece I
                              {0, 1, 0, 0},
                              {0, 1, 0, 0},
                              {0, 1, 0, 0},
                              {0, 1, 0, 0},
                          }},
                         {0,
                          0,
                          {// piece J
                           {1, 1, 1, 0},
                           {1, 0, 0, 0},
                           {0, 0, 0, 0},
                           {0, 0, 0, 0}}},
                         {0,
                          0,
                          {// piece L
                           {0, 0, 0, 1},
                           {0, 1, 1, 1},
                           {0, 0, 0, 0},
                           {0, 0, 0, 0}}},
                         {0,
                          0,
                          {// piece O
                           {0, 1, 1, 0},
                           {0, 1, 1, 0},
                           {0, 0, 0, 0},
                           {0, 0, 0, 0}}},
                         {0,
                          0,
                          {// piece S
                           {0, 0, 1, 1},
                           {0, 1, 1, 0},
                           {0, 0, 0, 0},
                           {0, 0, 0, 0}}},
                         {0,
                          0,
                          {// piece T
                           {0, 1, 0, 0},
                           {1, 1, 1, 0},
                           {0, 0, 0, 0},
                           {0, 0, 0, 0}}},
                         {0,
                          0,
                          {// piece Z
                           {1, 1, 0, 0},
                           {0, 1, 1, 0},
                           {0, 0, 0, 0},
                           {0, 0, 0, 0}}}};

  Tetromino actual_piece = pieces[rand() % 7];
  actual_piece.x = 3; // initial position: col 3
  actual_piece.y = 0; // initial position: row 0 (top)

  Uint32 last_fall_time = 0;
  const int gravity_delay = 500; // the tetromino will fall every 500ms

  int running = 1;
  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = 0;
      }
      if (event.type == SDL_KEYDOWN) {

        Tetromino collision_test_piece =
            actual_piece; // temp piece for detect collision
        switch (event.key.keysym.sym) {
        case SDLK_LEFT:
          collision_test_piece.x--;
          break;
        case SDLK_RIGHT:
          collision_test_piece.x++;
          break;
        case SDLK_DOWN:
          collision_test_piece.y++;
          break;
        }

        if (!check_collision(collision_test_piece, grid)) {
          actual_piece = collision_test_piece;
        }
      }
    }

    Uint32 actual_time = SDL_GetTicks();
    if (actual_time > last_fall_time + gravity_delay) { // gravity logic
      Tetromino temp_gravity_piece = actual_piece;
      temp_gravity_piece.y++;

      if (!check_collision(temp_gravity_piece, grid)) {
        actual_piece.y++;
      } else {
        fix_piece_on_grid(actual_piece, grid);
        actual_piece = pieces[rand() % 7];
        actual_piece.x = 3;
        actual_piece.y = 0;
      }
      last_fall_time = actual_time;
    }

    // Clear the window with background color (light gray)
    // SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_Color color = {30, 30, 30, 255};
    set_render_draw_SDL_Color(renderer, &color);
    SDL_RenderClear(renderer);

    // Draw the grid
    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        SDL_Rect rect = {j * BLOCK_SIZE, i * BLOCK_SIZE, BLOCK_SIZE,
                         BLOCK_SIZE};
        SDL_RenderDrawRect(renderer, &rect);
      }
    }

    // Draw the actual piece and it contour
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (actual_piece.shape[i][j] == 1) {
          int x = (actual_piece.x + j) * BLOCK_SIZE;
          int y = (actual_piece.y + i) * BLOCK_SIZE;

          SDL_Rect contour_rect = {x, y, BLOCK_SIZE, BLOCK_SIZE};
          SDL_Rect piece_block = {x + 1, y + 1, BLOCK_SIZE - 2, BLOCK_SIZE - 2};

          SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
          SDL_RenderDrawRect(renderer, &contour_rect);

          SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
          SDL_RenderFillRect(renderer, &piece_block);
        }
      }
    }

    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        if (grid[i][j] != 0) {
          SDL_Rect fixed_block = {j * BLOCK_SIZE, i * BLOCK_SIZE, BLOCK_SIZE,
                                  BLOCK_SIZE};
          SDL_RenderFillRect(renderer, &fixed_block);
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
