#include "backend.h"

int mayItGoDown() {
  int res = 1;
  GameInfo_t *stats = getGameInfo_t();
  Tblock *temp = stats->falling;
  for (int j = 0; j < CELLS; j++) {
    int x = temp[j].loc.col;
    int y = temp[j].loc.row;

    if (temp[j].loc.row == HEIGHT - 1) {
      res = 0;
    } else if (stats->field[y + 1][x] == 1) {
      int temp_res = 0;
      for (int i = 0; i < CELLS; i++) {
        if (stats->field[y + 1][x] == 1 && temp[i].loc.row == y + 1 &&
            temp[i].loc.col == x) {
          temp_res++;
        }
      }
      if (!temp_res) {
        res = 0;
      }
    }
  }
  return res;
}

int mayItRotate() {
  int res = 1;
  GameInfo_t *stats = getGameInfo_t();
  Tblock *temp = stats->falling;
  int orintation = (temp[0].orintation + 1) % 4;

  Tlocation cell_old = getTetr(temp[0].type, temp[0].orintation, 0);
  int diff_y = temp[0].loc.row - cell_old.row;
  int diff_x = temp[0].loc.col - cell_old.col;
  for (int i = 0; i < CELLS; i++) {
    Tlocation cell_new = getTetr(temp[i].type, orintation, i);
    if (cell_new.row + diff_y == HEIGHT || cell_new.col + diff_x == WIDTH ||
        cell_new.col + diff_x < 0) {
      res = 0;
    } else if (stats->field[cell_new.row + diff_y][cell_new.col + diff_x] ==
               1) {
      int temp_res = 0;
      for (int j = 0; j < CELLS; j++) {
        if (temp[j].loc.col == cell_new.col + diff_x &&
            temp[j].loc.row == cell_new.row + diff_y) {
          temp_res++;
        }
      }
      if (!temp_res) {
        res = 0;
      }
    }
  }
  return res;
}
int mayItGoLeft() {
  int res = 1;
  GameInfo_t *stats = getGameInfo_t();
  Tblock *temp = stats->falling;
  for (int j = 0; j < CELLS; j++) {
    int x = temp[j].loc.col;
    int y = temp[j].loc.row;

    if (temp[j].loc.col == 0) {
      res = 0;
    } else if (stats->field[y][x - 1] == 1) {
      int temp_res = 0;
      int count_n = 0;
      for (int i = 0; i < CELLS; i++) {
          if (x - 1 == temp[i].loc.col  && temp[i].loc.row == y) {
            count_n++;
          }
      }
      for (int i = 0; i < CELLS; i++) {
        if (stats->field[y][x - 1] == 1 && temp[i].loc.col == x && temp[i].loc.row == y) {
          temp_res++;
        }
      }
      if (temp_res > count_n) {
        res = 0;
      }
    }
  }

  return res;
}

int mayItGoRight() {
  int res = 1;
  GameInfo_t *stats = getGameInfo_t();
  Tblock *temp = stats->falling;
  for (int j = 0; j < CELLS; j++) {
    int x = temp[j].loc.col;
    int y = temp[j].loc.row;

    if (temp[j].loc.col == WIDTH - 1) {
      res = 0;
    } else if (stats->field[y][x + 1] == 1) {
      int temp_res = 0;
      int count_n = 0;
      for (int i = 0; i < CELLS; i++) {
          if (x + 1 == temp[i].loc.col  && temp[i].loc.row == y) {
            count_n++;
          }
      }
      for (int i = 0; i < CELLS; i++) {
        if (stats->field[y][x + 1] == 1 && temp[i].loc.col == x && temp[i].loc.row == y) {
          temp_res++;
        }
      }
      if (temp_res > count_n) {
        res = 0;
      }
    }
  }
  return res;
}

void rotateFigure() {
  GameInfo_t *stats = getGameInfo_t();
  if (mayItRotate()) {
    Tlocation cell_old =
        getTetr(stats->falling[0].type, stats->falling[0].orintation, 0);
    int diff_y = stats->falling[0].loc.row - cell_old.row;
    int diff_x = stats->falling[0].loc.col - cell_old.col;
    rmTetraminoFromField();
    int orintation = (stats->falling[0].orintation + 1) % 4;
    for (int i = 0; i < CELLS; i++) {
      Tlocation cell_new = getTetr(stats->falling[i].type, orintation, i);

      stats->falling[i].orintation = orintation;
      stats->falling[i].loc.row = cell_new.row + diff_y;
      stats->falling[i].loc.col = cell_new.col + diff_x;
      stats->field[cell_new.row + diff_y][cell_new.col + diff_x] = 1;
    }
  }
}

void deleteLines() {
  GameInfo_t *stats = getGameInfo_t();
  int deleted_lines = 0;
  for (int i = 1; i < HEIGHT; i++) {
    if (fullLine(i)) {
      for (int j = i; j > 0; j--) {
        memset(stats->field[j], 0, 40);
        memcpy(stats->field[j], stats->field[j - 1], 40);
      }
      deleted_lines++;
    }
  }
  if (deleted_lines) {
    switch (deleted_lines)
    {
    case 1:
      stats->score += 100;
      break;
    case 2:
      stats->score += 300;
      break;
    case 3:
      stats->score += 700;
      break;
    case 4:
      stats->score += 1500;
      break;
    default:
      break;
    }
   
    stats->level = stats->score / 600 + 1;
  }
}

int fastPow(int degree) {
  int res = 1;
  for (int i = 0; i < degree; i++) {
    res *= 2;
  }
  return res;
}

void moveFigure(UserAction_t direction) {
  GameInfo_t *stats = getGameInfo_t();
  if (stats->pause == 0 && stats->started) {
    if (direction == Down) {
      while (mayItGoDown()) {
        moveDown();
      }
    } else if (direction == Left && mayItGoLeft()) {
      moveLeft();
    } else if (direction == Right && mayItGoRight()) {
      moveRight();
    }
  }
}
void moveLeft() {
  GameInfo_t *stats = getGameInfo_t();
  int x, y;
  rmTetraminoFromField();
  for (int i = 0; i < CELLS; i++) {
    x = stats->falling[i].loc.col;
    y = stats->falling[i].loc.row;
    stats->falling[i].loc.col = x - 1;
    stats->field[y][x - 1] = 1;
  }
}

void moveRight() {
  GameInfo_t *stats = getGameInfo_t();
  int x, y;

  rmTetraminoFromField();
  for (int i = 0; i < CELLS; i++) {
    x = stats->falling[i].loc.col;
    y = stats->falling[i].loc.row;
    stats->falling[i].loc.col = x + 1;
    stats->field[y][x + 1] = 1;
  }
}

Tlocation getTetr(int tetramino, int orintation, int cells) {
  static const Tlocation info[TETRAMINOS][ORI][CELLS] = {

      {{{1, 0}, {1, 1}, {1, 2}, {1, 3}},
       {{0, 2}, {1, 2}, {2, 2}, {3, 2}},
       {{3, 0}, {3, 1}, {3, 2}, {3, 3}},
       {{0, 1}, {1, 1}, {2, 1}, {3, 1}}},

      {{{0, 0}, {1, 0}, {1, 1}, {1, 2}},
       {{0, 1}, {0, 2}, {1, 1}, {2, 1}},
       {{1, 0}, {1, 1}, {1, 2}, {2, 2}},
       {{0, 1}, {1, 1}, {2, 0}, {2, 1}}},

      {{{0, 2}, {1, 0}, {1, 1}, {1, 2}},
       {{0, 1}, {1, 1}, {2, 1}, {2, 2}},
       {{1, 0}, {1, 1}, {1, 2}, {2, 0}},
       {{0, 0}, {0, 1}, {1, 1}, {2, 1}}},

      {{{0, 1}, {0, 2}, {1, 1}, {1, 2}},
       {{0, 1}, {0, 2}, {1, 1}, {1, 2}},
       {{0, 1}, {0, 2}, {1, 1}, {1, 2}},
       {{0, 1}, {0, 2}, {1, 1}, {1, 2}}},

      {{{0, 1}, {0, 2}, {1, 0}, {1, 1}},
       {{0, 1}, {1, 1}, {1, 2}, {2, 2}},
       {{1, 1}, {1, 2}, {2, 0}, {2, 1}},
       {{0, 0}, {1, 0}, {1, 1}, {2, 1}}},

      {{{0, 1}, {1, 0}, {1, 1}, {1, 2}},
       {{0, 1}, {1, 1}, {1, 2}, {2, 1}},
       {{1, 0}, {1, 1}, {1, 2}, {2, 1}},
       {{0, 1}, {1, 0}, {1, 1}, {2, 1}}},

      {{{0, 0}, {0, 1}, {1, 1}, {1, 2}},
       {{0, 2}, {1, 1}, {1, 2}, {2, 1}},
       {{1, 0}, {1, 1}, {2, 1}, {2, 2}},
       {{0, 1}, {1, 0}, {1, 1}, {2, 0}}},
  };
  return info[tetramino][orintation][cells];
}