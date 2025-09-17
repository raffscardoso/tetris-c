#include "game.h"

const int BLOCK_SIZE = 32;
const int WINDOW_WIDTH = COLS * BLOCK_SIZE;
const int WINDOW_HEIGHT = ROWS * BLOCK_SIZE;

Tetromino pieces[7];

void init_game(GameState *game) {
  srand(time(NULL));
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      game->grid[i][j] = 0;
    }
  }

  pieces[0] = (Tetromino){
      0, 0, {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}}; // I
  pieces[1] = (Tetromino){
      0, 0, {{0, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}}}; // J
  pieces[2] = (Tetromino){
      0, 0, {{0, 0, 0, 0}, {0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}}}; // L
  pieces[3] = (Tetromino){
      0, 0, {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}}; // O
  pieces[4] = (Tetromino){
      0, 0, {{0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}}}; // S
  pieces[5] = (Tetromino){
      0, 0, {{0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}}}; // T
  pieces[6] = (Tetromino){
      0, 0, {{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}}; // Z

  spawn_new_piece(game);

  game->running = 1;
  game->last_fall_time = 0;
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

  if (check_collision(game->actual_piece, game->grid))
    game->running = 0;
}

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

void rotate_piece(Tetromino *piece) {
  Tetromino temp = *piece;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      piece->shape[i][j] = temp.shape[3 - j][i];
    }
  }
}

void handle_input(GameState *game) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      game->running = 0;
    }
    if (event.type == SDL_KEYDOWN) {
      if (event.key.keysym.sym == SDLK_z) {
        Tetromino temp = game->actual_piece;
        while (!check_collision(temp, game->grid)) {
          game->actual_piece = temp;
          temp.y++;
        }
        fix_piece_on_grid(game->actual_piece, game->grid);
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
      }
      if (!check_collision(test_piece, game->grid)) {
        game->actual_piece = test_piece;
      }
    }
  }
}

void update_game(GameState *game) {
  const int gravity_delay = 500;
  Uint32 actual_time = SDL_GetTicks();
  if (actual_time > game->last_fall_time + gravity_delay) {
    Tetromino temp_gravity_piece = game->actual_piece;
    temp_gravity_piece.y++;

    if (!check_collision(temp_gravity_piece, game->grid)) {
      game->actual_piece.y++;
    } else {
      fix_piece_on_grid(game->actual_piece, game->grid);
      spawn_new_piece(game);
    }
    game->last_fall_time = actual_time;
  }
}
