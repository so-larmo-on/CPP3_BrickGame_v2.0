#include "model.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <time.h>

#include <cassert>
#include <cstdio>
#include <random>
using namespace s21;

GameInfo_t *Model::getGameInfo_s() {
  static GameInfo_t *stats = NULL;
  if (stats == NULL) {
    stats = new (GameInfo_t);
    if (stats != NULL) {
      stats->field = new int *[HEIGHT];
      if (stats->field != NULL) {
        for (int i = 0; i < HEIGHT; i++) {
          stats->field[i] = new int[WIDTH]();
        }
      } else {
        Model::errorQuit();
      }
      stats->faster = 1;
      stats->worm = new worm_part[200];
      stats->pause = 0;
      stats->started = 0;
      stats->stop = 0;
      stats->score = 0;
      stats->high_score = 0;
      stats->ticks = 1;
      stats->level = 1;
      stats->length = 4;
      stats->dir = Right;
      stats->next = nullptr;
    } else {
      Model::errorQuit();
    }
  }
  return stats;
}

void Model::startGame() {
  GameInfo_t *stats = Model::getGameInfo_s();
  int hi_score = -2;

  FILE *file = fopen("../record_snake.txt", "r+");
  if (file) {
    fscanf(file, "%d", &hi_score);
    fclose(file);
  }
  stats->high_score = hi_score;
  stats->started = 1;
  initWorm();
}

void Model::playAgain() {
  GameInfo_t *stats = Model::getGameInfo_s();
  stats->score = 0;
  stats->level = 1;
  stats->length = WORMSIZE;
  stats->dir = Right;
  stats->stop = 0;
  stats->pause = 0;
  initWorm();
}

void Model::initWorm() {
  GameInfo_t *stats = Model::getGameInfo_s();
  int x = 4, y = 1, i;

  if (stats->worm == NULL) {
    errorQuit();
  }
  for (i = 0; i < stats->length; i++) {
    stats->worm[i].x = x--;
    stats->worm[i].y = y;
  }
  placeFood();
  putFigureOnField();
}

void Model::putFigureOnField() {
  GameInfo_t *stats = Model::getGameInfo_s();
  worm_part *temp = stats->worm;
  for (int i = 0; i < stats->length; i++) {
    if (stats->started && stats->stop == 0) {
      if (i == 0) {
        stats->field[temp[i].y][temp[i].x] = 3;
      } else {
        stats->field[temp[i].y][temp[i].x] = 1;
      }
    }
  }
}

void Model::placeFood() {
  GameInfo_t *stats = Model::getGameInfo_s();
  std::mt19937 engine1;
  std::random_device device1;
  engine1.seed(device1());
  std::mt19937 engine2;
  std::random_device device2;
  engine2.seed(device2());
  stats->faster = 0;
  int x = engine1() % 10, y = engine2() % 20;

  while (stats->field[y][x] == 1) {
    x = engine1() % 10;
    y = engine2() % 20;
  }
  stats->field[y][x] = 2;
  stats->faster = 1;
}

void Model::moveWormDir() {
  GameInfo_t *stats = Model::getGameInfo_s();
  int x1 = stats->worm[0].x;
  int y1 = stats->worm[0].y;
  if (stats->dir == Left) {
    stats->worm[0].x = x1 - 1;
  }
  if (stats->dir == Right) {
    stats->worm[0].x = x1 + 1;
  }
  if (stats->dir == Down) {
    stats->worm[0].y = y1 + 1;
  }
  if (stats->dir == Up) {
    stats->worm[0].y = y1 - 1;
  }
}

void Model::moveWorm() {
  GameInfo_t *stats = Model::getGameInfo_s();
  bool to_place_food = 0;
  rmWormFromField();
  int x1 = stats->worm[0].x;
  int y1 = stats->worm[0].y;
  moveWormDir();
  if (mayItGo(0) && stats->field[stats->worm[0].y][stats->worm[0].x] == 2) {
    stats->score++;
    if (stats->score % 5 == 0) {
      stats->level++;
    }
    stats->length++;
    to_place_food = 1;
  }
  if (mayItGo(0)) {
    stats->field[stats->worm[0].y][stats->worm[0].x] = 3;
    for (int i = 1; i < stats->length; i++) {
      int x = stats->worm[i].x, y = stats->worm[i].y;
      stats->worm[i].y = y1;
      stats->worm[i].x = x1;
      x1 = x;
      y1 = y;
      if (stats->field[stats->worm[i].y][stats->worm[i].x] == 1) {
        TerminatePushed();
        break;
      } else {
        stats->field[stats->worm[i].y][stats->worm[i].x] = 1;
      }
    }
    if (to_place_food) {
      placeFood();
      to_place_food = 0;
    }
  }
}

bool Model::mayItGo(int i) {
  GameInfo_t *stats = Model::getGameInfo_s();

  if (stats->worm[i].x < 0 || stats->worm[i].x > WIDTH - 1 ||
      stats->worm[i].y < 0 || stats->worm[i].y > HEIGHT - 1) {
    Model::TerminatePushed();
    return false;
  }
  return true;
}
void Model::rmWormFromField() {
  GameInfo_t *stats = Model::getGameInfo_s();
  for (int i = 0; i < stats->length; i++) {
    int x = stats->worm[i].x;
    int y = stats->worm[i].y;
    mayItGo(i);
    stats->field[y][x] = 0;
  }
}

void Model::changeDirection(UserAction_t direction) {
  GameInfo_t *stats = Model::getGameInfo_s();
  if (stats->dir == Left || stats->dir == Right) {
    if (direction == Up || direction == Down) {
      if (direction == Up) {
        stats->dir = Up;
      } else {
        stats->dir = Down;
      }
    }

  } else if (stats->dir == Up || stats->dir == Down) {
    if (direction == Right || direction == Left) {
      if (direction == Right) {
        stats->dir = Right;
      } else {
        stats->dir = Left;
      }
    }
  }
}

void Model::moveFaster() {
  GameInfo_t *stats = Model::getGameInfo_s();
  if (stats->pause == 0 && stats->started == 1 && stats->stop == 0 &&
      stats->faster) {
    moveWorm();
  }
}

void Model::pauseGame() {
  GameInfo_t *stats = Model::getGameInfo_s();
  if (stats->pause == 1) {
    stats->pause = 0;
  } else {
    stats->pause = 1;
  }
}

int Model::getGravity(int index) {
  const int speed[11] = {// 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10
                         0, 27, 23, 17, 15, 13, 12, 11, 9, 8, 7};

  return speed[index];
}

void Model::TerminatePushed() {
  GameInfo_t *stats = Model::getGameInfo_s();

  for (int j = 0; j < stats->length; j++) {
    stats->worm[j].y = -1;
    stats->worm[j].x = -1;
  }
  if (!stats->stop) {
    for (int i = 0; i < stats->length; i++) {
      stats->worm[i].x = -1;
      stats->worm[i].y = -1;
    }
  }
  stats->stop = 1;
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      stats->field[i][j] = 0;
    }
  }
}

void Model::freeMap() {
  GameInfo_t *stats = Model::getGameInfo_s();
  for (int i = 0; i < HEIGHT; i++) {
    delete (stats->field[i]);
  }
  delete (stats->field);
  exit(EXIT_SUCCESS);
}

void Model::errorQuit() {
  std::perror("couldnt manage to allocate memory");
  exit(EXIT_FAILURE);
}
