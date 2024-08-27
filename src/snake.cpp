/*!
 * \mainpage
 * \author grangerm
 * \version 1.0
 *
 * \section intro_sec Snake
 * Проект создан при помощи:
 * 1. C C++ languages
 * 2. ncurses
 * 3. Qt
 * 3. Doxygen
 *
 * \section brief_sec Brief
 * BrickGame — популярная портативная консоль 90-ых годов с несколькими тысячами
 * встроенными играми, разработанная в Китае. Изначально была копией
 * разработанной в СССР и выпущенной Nintendo в рамках платформы GameBoy игры
 * «Тетрис», но включала в себя также и множество других игр, которые
 * добавлялись с течением времени. Консоль имела небольшой экранчик с игровым
 * полем размера 10х20, представляющим из себя матрицу «пикселей». Справа от
 * поля находилось табло с цифровой индикацией состояния текущей игры, рекордами
 * и прочей дополнительной информацией. Самыми распространенными играми на
 * BrickGame были: тетрис, танки, гонки, фроггер и змейка.
 *
 * В данном проекте реализована игра из серии BrickGame -
 * Snake.
 *
 */
#include "snake.h"

#include "brick_game/snake/controller.h"
#include "brick_game/snake/model.h"
#ifdef SNAKE_CLI
#include "./gui/cli/cview.h"
#endif
#ifdef SNAKE_DESK
#include "gui/desktop/game.h"
#endif

using namespace s21;

int main(int argc, char *argv[]) {  //

  Model model;
  Controller controller(&model);
#ifdef SNAKE_CLI
  (void)argc;
  (void)argv;
  controller.gameLoop_c();
#endif

#ifdef SNAKE_DESK
  QApplication app(argc, argv);
  Game game(&controller);

  return app.exec();
#endif

  return 0;
}
