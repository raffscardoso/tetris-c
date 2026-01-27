#include "game.h"
#include <stdio.h>
#include <stdlib.h>

const int BLOCK_SIZE = 32;
const int WINDOW_WIDTH = COLS * BLOCK_SIZE;
const int WINDOW_HEIGHT = ROWS * BLOCK_SIZE;
#define MAX_HIGH_SCORES 5
#define HIGH_SCORE_FILE "highscores.txt"

Tetromino pieces[7];

int high_scores[MAX_HIGH_SCORES] = {0};

void load_high_scores(int *scores, int count) {
    FILE *file = fopen(HIGH_SCORE_FILE, "r");
    if (file) {
        for (int i = 0; i < count; i++) {
            if (fscanf(file, "%d", &scores[i]) != 1) {
                scores[i] = 0;
            }
        }
        fclose(file);
    } else {
        for (int i = 0; i < count; i++) {
            scores[i] = 0;
        }
    }
}

void save_high_scores_to_file(int *scores, int count) {
    FILE *file = fopen(HIGH_SCORE_FILE, "w");
    if (file) {
        for (int i = 0; i < count; i++) {
            fprintf(file, "%d\n", scores[i]);
        }
        fclose(file);
    }
}

void save_high_score(int score) {
    load_high_scores(high_scores, MAX_HIGH_SCORES);
    
    // Check if score qualifies
    int inserted = 0;
    for (int i = 0; i < MAX_HIGH_SCORES; i++) {
        if (score > high_scores[i]) {
            // Shift lower scores down
            for (int j = MAX_HIGH_SCORES - 1; j > i; j--) {
                high_scores[j] = high_scores[j - 1];
            }
            high_scores[i] = score;
            inserted = 1;
            break;
        }
    }
    
    if (inserted) {
        save_high_scores_to_file(high_scores, MAX_HIGH_SCORES);
    }
}

int* get_high_scores() {
    load_high_scores(high_scores, MAX_HIGH_SCORES);
    return high_scores;
}

int get_high_score_count() {
    return MAX_HIGH_SCORES;
}

// Game Logic

void reset_grid(GameState *game) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            game->grid[i][j] = 0;
        }
    }
}

void init_game(GameState *game) {
  srand(time(NULL));
  reset_grid(game);

  pieces[0] = (Tetromino){
      0, 0, {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}, 1}; // I
  pieces[1] = (Tetromino){
      0, 0, {{0, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}}, 2}; // J
  pieces[2] = (Tetromino){
      0, 0, {{0, 0, 0, 0}, {0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}}, 3}; // L
  pieces[3] = (Tetromino){
      0, 0, {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}, 4}; // O
  pieces[4] = (Tetromino){
      0, 0, {{0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}}, 5}; // S
  pieces[5] = (Tetromino){
      0, 0, {{0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}}, 6}; // T
  pieces[6] = (Tetromino){
      0, 0, {{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}, 7}; // Z

  
  game->score = 0;
  game->running = 1;
  game->last_fall_time = 0;
  game->state = MENU;
  game->menu_option = 0;
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
  return 0;
}

void spawn_new_piece(GameState *game) {
  game->actual_piece = pieces[rand() % 7];
  game->actual_piece.x = 3;
  game->actual_piece.y = 0;

  if (check_collision(game->actual_piece, game->grid)) {
      save_high_score(game->score);
      game->state = GAME_OVER;
  }
}

void fix_piece_on_grid(Tetromino piece, int grid[ROWS][COLS]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (piece.shape[i][j] == 1) {
        int pos_x = piece.x + j;
        int pos_y = piece.y + i;

        grid[pos_y][pos_x] = piece.color;
      }
    }
  }
}

void rotate_piece(Tetromino *piece) {
  Tetromino temp = *piece;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      piece->shape[i][j] = temp.shape[3 - j][i];
    }
  }
}

void start_new_game(GameState *game) {
    reset_grid(game);
    game->score = 0;
    spawn_new_piece(game);
    game->state = PLAYING;
}

void handle_input(GameState *game) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      game->running = 0;
    }
    if (event.type == SDL_KEYDOWN) {
        if (game->state == MENU) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    game->menu_option--;
                    if (game->menu_option < 0) game->menu_option = 2;
                    break;
                case SDLK_DOWN:
                    game->menu_option++;
                    if (game->menu_option > 2) game->menu_option = 0;
                    break;
                case SDLK_RETURN:
                case SDLK_KP_ENTER:
                    if (game->menu_option == 0) { // Start
                        start_new_game(game);
                    } else if (game->menu_option == 1) { // High Scores
                        game->state = HIGHSCORES;
                    } else if (game->menu_option == 2) { // Exit
                        game->running = 0;
                    }
                    break;
            }
        } else if (game->state == HIGHSCORES) {
            if (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_RETURN) {
                game->state = MENU;
            }
        } else if (game->state == GAME_OVER) {
            if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_ESCAPE) {
                game->state = MENU;
            }
        } else if (game->state == PLAYING) {
            if (event.key.keysym.sym == SDLK_z) {
                Tetromino temp = game->actual_piece;
                while (!check_collision(temp, game->grid)) {
                game->actual_piece = temp;
                temp.y++;
                }
                fix_piece_on_grid(game->actual_piece, game->grid);
                check_and_clear_lines(game);
                spawn_new_piece(game);
            }
            
            Tetromino test_piece = game->actual_piece;
            switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                test_piece.x--;
                break;
            case SDLK_RIGHT:
                test_piece.x++;
                break;
            case SDLK_DOWN:
                test_piece.y++;
                break;
            case SDLK_UP:
                rotate_piece(&test_piece);
                break;
            case SDLK_ESCAPE: // goes back to menu
                game->state = MENU; // TODO: Pause menu
                break;
            }
            
            if (game->state == PLAYING && !check_collision(test_piece, game->grid)) {
                game->actual_piece = test_piece;
            }
        }
    }
  }
}

void update_game(GameState *game) {
  if (game->state != PLAYING) return;

  const int gravity_delay = 500;
  Uint32 actual_time = SDL_GetTicks();
  if (actual_time > game->last_fall_time + gravity_delay) {
    Tetromino temp_gravity_piece = game->actual_piece;
    temp_gravity_piece.y++;

    if (!check_collision(temp_gravity_piece, game->grid)) {
      game->actual_piece.y++;
    } else {
      fix_piece_on_grid(game->actual_piece, game->grid);
      check_and_clear_lines(game);
      spawn_new_piece(game);
    }
    game->last_fall_time = actual_time;
  }
}

void score_calc(GameState *game, int lines_cleared) {

  if (lines_cleared == 1)
    game->score += 100;
  if (lines_cleared == 2)
    game->score += 300;
  if (lines_cleared == 3)
    game->score += 500;
  if (lines_cleared == 4)
    game->score += 800;
}

void check_and_clear_lines(GameState *game) {
  int lines_cleared = 0;

  for (int i = ROWS - 1; i >= 0; i--) {
    int line_is_full = 1;
    for (int j = 0; j < COLS; j++) {
      if (game->grid[i][j] == 0) {
        line_is_full = 0;
        break;
      }
    }
    if (line_is_full) {
      lines_cleared++;
      for (int k = i; k > 0; k--) {
        for (int j = 0; j < COLS; j++) {
          game->grid[k][j] = game->grid[k - 1][j];
        }
      }

      // cleaning the first row
      for (int j = 0; j < COLS; j++)
        game->grid[0][j] = 0;
      i++;
    }
  }
  score_calc(game, lines_cleared);
}
