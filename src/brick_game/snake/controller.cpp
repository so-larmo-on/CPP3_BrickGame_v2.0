
#include "controller.h"

#include <stdio.h>
#include <stdlib.h>
#ifdef SNAKE_CLI
extern "C" {
#include "../../gui/cli/cview.h"
}
#include <curses.h>
#endif
using namespace s21;

void Controller::gameLoop_c() {
  while (1) {
    GameInfo_t *stats = updateCurrentState();

#ifdef SNAKE_CLI
    updateField(stats);
    userInput(stats->action, stats->started);
#endif
    if (stats->pause == 0 && stats->started == 1 && stats->stop == 0) {
      if (stats->ticks >= getGravity_c(stats->level)) {
        stats->ticks = 0;

        moveWorm_c();
      }

      stats->high_score =
          stats->score > stats->high_score ? stats->score : stats->high_score;
      stats->ticks++;
    }
#ifdef SNAKE_DESK
    break;
#endif
  }
}

GameInfo_t *Controller::updateCurrentState() {
  GameInfo_t *stats = model->getGameInfo_s();
  return stats;
}

void Controller::startGame_c() { model->startGame(); }
void Controller::moveWorm_c() { model->moveWorm(); }
int Controller::getGravity_c(int grav) { return model->getGravity(grav); }
void Controller::quit() {
  GameInfo_t *stats = updateCurrentState();
  FILE *file = fopen("../record_snake.txt", "r+");
  if (file) {
    fprintf(file, "%d", stats->high_score);
    fclose(file);
  }

  model->freeMap();
  exit(EXIT_SUCCESS);
}

void Controller::moveFaster_c() { model->moveFaster(); }
void Controller::pauseGame_c() { model->pauseGame(); }
void Controller::changeDirection_c(UserAction_t action) {
  model->changeDirection(action);
}
void Controller::TerminatePushed_c() { model->TerminatePushed(); }
void Controller::userInput(UserAction_t action, bool hold) {
  GameInfo_t *stats = updateCurrentState();
  if (!hold && action == Start) {
    startGame_c();
  }
  if (hold) {
    switch (action) {
      case Start:
        break;
      case Pause:
        pauseGame_c();
        break;
      case Action:
        moveFaster_c();
        break;
      case Down:
        changeDirection_c(action);
        break;
      case Left:
        changeDirection_c(action);
        break;
      case Right:
        changeDirection_c(action);
        break;
      case Up:
        changeDirection_c(action);
        break;
      case Terminate:
        TerminatePushed_c();
        break;
      case Quit:
        quit();
        break;
      case Again:
        model->playAgain();
      default:
        break;
    }
  }
  stats->action = Noact;
}
