#include "sdl_handler.h"
#include "game.h"
#include "font.h"
#include <stdio.h>
#include <string.h>

SDL_Color tetromino_colors[] = {
    {0, 0, 0, 255},     {0, 255, 255, 255}, // I piece (Cyan)
    {0, 0, 128, 255},                       // J piece (BLue)
    {255, 165, 0, 255},                     // L piece (orange)
    {255, 255, 0, 255},                     // O piece (yellow)
    {0, 128, 0, 255},                       // S piece (green)
    {128, 0, 128, 255},                     // T piece (purple)
    {255, 0, 0, 255}                        // Z piece (red)
};

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

void render_game(SDL_Handler *sdl_handler, GameState *game) {
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

        set_render_draw_SDL_Color(sdl_handler->renderer,
                                  &tetromino_colors[game->actual_piece.color]);
        SDL_RenderFillRect(sdl_handler->renderer, &piece_block);
      }
    }
  }

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (game->grid[i][j] != 0) {
        SDL_Rect fixed_block = {j * BLOCK_SIZE, i * BLOCK_SIZE, BLOCK_SIZE,
                                BLOCK_SIZE};
        set_render_draw_SDL_Color(sdl_handler->renderer,
                                  &tetromino_colors[game->grid[i][j]]);
        SDL_RenderFillRect(sdl_handler->renderer, &fixed_block);
      }
    }
  }
  
  // Draw score
  char score_text[32];
  sprintf(score_text, "SCORE %d", game->score);
  SDL_Color white = {255, 255, 255, 255};
  draw_string(sdl_handler->renderer, 10, 10, score_text, 2, white);
}

void render_menu(SDL_Handler *sdl_handler, GameState *game) {
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color selected = {255, 255, 0, 255}; // Yellow
    SDL_Color dim = {150, 150, 150, 255};

    int scale = 4;
    int center_x = WINDOW_WIDTH / 2 - (5 * 4 * scale) / 2; // Approx center
    int start_y = 150;

    draw_string(sdl_handler->renderer, center_x - 20, 50, "TETRIS", 6, white);

    draw_string(sdl_handler->renderer, center_x, start_y, "START", scale, game->menu_option == 0 ? selected : dim);
    draw_string(sdl_handler->renderer, center_x, start_y + 80, "SCORES", scale, game->menu_option == 1 ? selected : dim);
    draw_string(sdl_handler->renderer, center_x, start_y + 160, "EXIT", scale, game->menu_option == 2 ? selected : dim);
}

void render_highscores(SDL_Handler *sdl_handler, GameState *game) {
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color red = {255, 0, 0, 255};
    
    draw_string(sdl_handler->renderer, 40, 50, "HIGH SCORES", 4, red);

    int *scores = get_high_scores();
    int count = get_high_score_count();

    for (int i = 0; i < count; i++) {
        char score_text[32];
        sprintf(score_text, "%d %d", i + 1, scores[i]);
        draw_string(sdl_handler->renderer, 60, 150 + i * 50, score_text, 3, white);
    }
    
    draw_string(sdl_handler->renderer, 60, 500, "PRESS ENTER", 2, white);
}

void render_gameover(SDL_Handler *sdl_handler, GameState *game) {
    render_game(sdl_handler, game); // Draw background game

    // Overlay
    SDL_SetRenderDrawBlendMode(sdl_handler->renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(sdl_handler->renderer, 0, 0, 0, 200);
    SDL_Rect overlay = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_RenderFillRect(sdl_handler->renderer, &overlay);
    SDL_SetRenderDrawBlendMode(sdl_handler->renderer, SDL_BLENDMODE_NONE);

    SDL_Color red = {255, 0, 0, 255};
    SDL_Color white = {255, 255, 255, 255};

    draw_string(sdl_handler->renderer, 40, 200, "GAME OVER", 5, red);
    
    char score_text[32];
    sprintf(score_text, "SCORE %d", game->score);
    draw_string(sdl_handler->renderer, 60, 300, score_text, 3, white);
    
    draw_string(sdl_handler->renderer, 60, 400, "PRESS ENTER", 2, white);
}

void render(SDL_Handler *sdl_handler, GameState *game) {
  SDL_Color color = {30, 30, 30, 255};
  set_render_draw_SDL_Color(sdl_handler->renderer, &color);
  SDL_RenderClear(sdl_handler->renderer);

  switch (game->state) {
      case MENU:
          render_menu(sdl_handler, game);
          break;
      case PLAYING:
          render_game(sdl_handler, game);
          break;
      case HIGHSCORES:
          render_highscores(sdl_handler, game);
          break;
      case GAME_OVER:
          render_gameover(sdl_handler, game);
          break;
  }

  SDL_RenderPresent(sdl_handler->renderer);
}

void cleanup_sdl(SDL_Handler *sdl_handler) {
  SDL_DestroyRenderer(sdl_handler->renderer);
  SDL_DestroyWindow(sdl_handler->window);
  SDL_Quit();
}