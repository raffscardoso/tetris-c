#include <emscripten.h>
#include "game.h"
#include "sdl_handler.h"

typedef struct {
  SDL_Handler *sdl_handler;
  GameState *game;
} MainLoopContext;

void main_loop(void *arg) {
  MainLoopContext *ctx = (MainLoopContext *)arg;
  handle_input(ctx->game);
  update_game(ctx->game);
  render(ctx->sdl_handler, ctx->game);

  if (!ctx->game->running) {
    emscripten_cancel_main_loop();
  }
}

int main(int argc, char *argv[]) {
  SDL_Handler sdl_handler;
  if (init_sdl(&sdl_handler) != 0) {
    return 1;
  }

  GameState game;
  init_game(&game);

  MainLoopContext ctx = {&sdl_handler, &game};

  // 0 fps means use requestAnimationFrame (recommended), 1 means simulate infinite loop
  emscripten_set_main_loop_arg(main_loop, &ctx, 0, 1);

  cleanup_sdl(&sdl_handler);

  return 0;
}
