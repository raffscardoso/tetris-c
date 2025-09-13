#include "sdl_handler.h"
#include "game.h"
#include <stdio.h>

int init_sdl(SDL_Handler *sdl_handler) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Error on initializing SDL: %s\n", SDL_GetError());
    return 1;
  }

  sdl_handler->window =
      SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

  if (sdl_handler->window == NULL) {
    printf("Error on window creation: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  sdl_handler->renderer =
      SDL_CreateRenderer(sdl_handler->window, -1, SDL_RENDERER_ACCELERATED);
  if (sdl_handler->renderer == NULL) {
    printf("Error on renderer creation: %s\n", SDL_GetError());
    SDL_DestroyWindow(sdl_handler->window);
    SDL_Quit();
    return 1;
  }
  return 0;
}

void set_render_draw_SDL_Color(SDL_Renderer *renderer, SDL_Color *color) {
  SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
}

void render(SDL_Handler *sdl_handler, GameState *game) {
  SDL_Color color = {30, 30, 30, 255};
  set_render_draw_SDL_Color(sdl_handler->renderer, &color);
  SDL_RenderClear(sdl_handler->renderer);

  SDL_SetRenderDrawColor(sdl_handler->renderer, 80, 80, 80, 255);
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      SDL_Rect rect = {j * BLOCK_SIZE, i * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
      SDL_RenderDrawRect(sdl_handler->renderer, &rect);
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (game->actual_piece.shape[i][j] == 1) {
        int x = (game->actual_piece.x + j) * BLOCK_SIZE;
        int y = (game->actual_piece.y + i) * BLOCK_SIZE;

        SDL_Rect contour_rect = {x, y, BLOCK_SIZE, BLOCK_SIZE};
        SDL_Rect piece_block = {x + 1, y + 1, BLOCK_SIZE - 2, BLOCK_SIZE - 2};

        SDL_SetRenderDrawColor(sdl_handler->renderer, 64, 64, 64, 255);
        SDL_RenderDrawRect(sdl_handler->renderer, &contour_rect);

        SDL_SetRenderDrawColor(sdl_handler->renderer, 255, 255, 0, 255);
        SDL_RenderFillRect(sdl_handler->renderer, &piece_block);
      }
    }
  }

  SDL_SetRenderDrawColor(sdl_handler->renderer, 200, 200, 200, 255);
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (game->grid[i][j] != 0) {
        SDL_Rect fixed_block = {j * BLOCK_SIZE, i * BLOCK_SIZE, BLOCK_SIZE,
                                BLOCK_SIZE};
        SDL_RenderFillRect(sdl_handler->renderer, &fixed_block);
      }
    }
  }

  SDL_RenderPresent(sdl_handler->renderer);
}

void cleanup_sdl(SDL_Handler *sdl_handler) {
  SDL_DestroyRenderer(sdl_handler->renderer);
  SDL_DestroyWindow(sdl_handler->window);
  SDL_Quit();
}
