
#include "tetris.h"

extern "C" {
#include "brick_game/tetris/backend.h"
}
#ifdef TETRIS_CLI
#include "./gui/cli/cview.h"

#endif
#ifdef TETRIS_DESK
#include "gui/desktop/game.h"
#endif

int main(int argc, char *argv[]) {
#ifdef TETRIS_CLI
  (void)argc;
  (void)argv;
  gameLoop();
#endif

#ifdef TETRIS_DESK
  QApplication app(argc, argv);
  Game game(nullptr);

  return app.exec();

#endif

  return 0;
}
