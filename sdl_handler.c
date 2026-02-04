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

    int scale_title = 6;
    int scale_menu = 4;
    int start_y = 150;

    const char *title = "TETRIS";
    int title_width = get_string_width(title, scale_title);
    draw_string(sdl_handler->renderer, (WINDOW_WIDTH - title_width) / 2, 50, title, scale_title, white);

    const char *opt1 = "START";
    int opt1_width = get_string_width(opt1, scale_menu);
    draw_string(sdl_handler->renderer, (WINDOW_WIDTH - opt1_width) / 2, start_y, opt1, scale_menu, game->menu_option == 0 ? selected : dim);

    const char *opt2 = "SCORES";
    int opt2_width = get_string_width(opt2, scale_menu);
    draw_string(sdl_handler->renderer, (WINDOW_WIDTH - opt2_width) / 2, start_y + 80, opt2, scale_menu, game->menu_option == 1 ? selected : dim);

    const char *opt3 = "EXIT";
    int opt3_width = get_string_width(opt3, scale_menu);
    draw_string(sdl_handler->renderer, (WINDOW_WIDTH - opt3_width) / 2, start_y + 160, opt3, scale_menu, game->menu_option == 2 ? selected : dim);
}

void render_highscores(SDL_Handler *sdl_handler, GameState *game) {
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color red = {255, 0, 0, 255};
    
    const char *title = "HIGH SCORES";
    int scale_title = 4;
    int title_width = get_string_width(title, scale_title);
    draw_string(sdl_handler->renderer, (WINDOW_WIDTH - title_width) / 2, 50, title, scale_title, red);

    int *scores = get_high_scores();
    int count = get_high_score_count();

    for (int i = 0; i < count; i++) {
        char score_text[32];
        sprintf(score_text, "%d %d", i + 1, scores[i]);
        int scale_score = 3;
        int score_width = get_string_width(score_text, scale_score);
        draw_string(sdl_handler->renderer, (WINDOW_WIDTH - score_width) / 2, 150 + i * 50, score_text, scale_score, white);
    }
    
    const char *msg = "PRESS ENTER";
    int scale_msg = 2;
    int msg_width = get_string_width(msg, scale_msg);
    draw_string(sdl_handler->renderer, (WINDOW_WIDTH - msg_width) / 2, 500, msg, scale_msg, white);
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

    const char *title = "GAME OVER";
    int scale_title = 5;
    int title_width = get_string_width(title, scale_title);
    draw_string(sdl_handler->renderer, (WINDOW_WIDTH - title_width) / 2, 200, title, scale_title, red);
    
    char score_text[32];
    sprintf(score_text, "SCORE %d", game->score);
    int scale_score = 3;
    int score_width = get_string_width(score_text, scale_score);
    draw_string(sdl_handler->renderer, (WINDOW_WIDTH - score_width) / 2, 300, score_text, scale_score, white);
    
    const char *msg = "PRESS ENTER";
    int scale_msg = 2;
    int msg_width = get_string_width(msg, scale_msg);
    draw_string(sdl_handler->renderer, (WINDOW_WIDTH - msg_width) / 2, 400, msg, scale_msg, white);
}

void render_pause(SDL_Handler *sdl_handler, GameState *game) {
    render_game(sdl_handler, game); // Draw background game

    // Overlay
    SDL_SetRenderDrawBlendMode(sdl_handler->renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(sdl_handler->renderer, 0, 0, 0, 200);
    SDL_Rect overlay = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_RenderFillRect(sdl_handler->renderer, &overlay);
    SDL_SetRenderDrawBlendMode(sdl_handler->renderer, SDL_BLENDMODE_NONE);

    SDL_Color white = {255, 255, 255, 255};
    SDL_Color selected = {255, 255, 0, 255}; // Yellow
    SDL_Color dim = {150, 150, 150, 255};

    const char *title = "PAUSED";
    int scale_title = 5;
    int title_width = get_string_width(title, scale_title);
    draw_string(sdl_handler->renderer, (WINDOW_WIDTH - title_width) / 2, 150, title, scale_title, white);

    const char *opt1 = "RESUME";
    int scale_menu = 4;
    int opt1_width = get_string_width(opt1, scale_menu);
    draw_string(sdl_handler->renderer, (WINDOW_WIDTH - opt1_width) / 2, 300, opt1, scale_menu, game->pause_option == 0 ? selected : dim);

    const char *opt2 = "QUIT";
    int opt2_width = get_string_width(opt2, scale_menu);
    draw_string(sdl_handler->renderer, (WINDOW_WIDTH - opt2_width) / 2, 380, opt2, scale_menu, game->pause_option == 1 ? selected : dim);
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
      case PAUSED:
          render_pause(sdl_handler, game);
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
