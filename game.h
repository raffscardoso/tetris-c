#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"
#include <time.h>

#define COLS 10
#define ROWS 20

extern const int BLOCK_SIZE;
extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

typedef struct {
  int x, y;
  int shape[4][4];
  int color;
} Tetromino;

typedef enum {
    MENU,
    PLAYING,
    PAUSED,
    HIGHSCORES,
    GAME_OVER
} State;

typedef struct {
  int grid[ROWS][COLS];
  Tetromino actual_piece;
  Uint32 last_fall_time;
  int running;
  int score;
  State state;
  int menu_option; 
  int pause_option; // 0: Resume, 1: Quit 
} GameState;

void init_game(GameState *game);
void handle_input(GameState *game);
void update_game(GameState *game);
void rotate_piece(Tetromino *piece);
void spawn_new_piece(GameState *game);
void check_and_clear_lines(GameState *game);
void score_calc(GameState *game, int lines_cleared);

void save_high_score(int score);
int* get_high_scores();
int get_high_score_count();

#endif // GAME_H
