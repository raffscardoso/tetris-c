#include "game.h"
#include "sdl_handler.h"

int main(int argc, char *argv[]) {
  SDL_Handler sdl_handler;
  if (init_sdl(&sdl_handler) != 0) {
    return 1;
  }

  GameState game;
  init_game(&game);

  while (game.running) {
    handle_input(&game);
    update_game(&game);
    render(&sdl_handler, &game);
  }

  cleanup_sdl(&sdl_handler);

  return 0;
}
