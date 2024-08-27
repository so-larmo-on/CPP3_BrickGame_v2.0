#include "cview.h"

#include <curses.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/ioctl.h>


void updateField(GameInfo_t *stats) {
    int key = getch();
    UserAction_t action;
    parseKey(key, &action, stats);
    stats->action = action;
    if (stats->started && !stats->stop) {
      clear();
      drawRecs(stats);
      drawField(stats);
      DrawNext(stats);

      refresh();

    } else if (stats->started == 0) {
      CURSINIT();
      drawStartMessage();
      start_color();
      init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
      init_pair(2, COLOR_BLUE, COLOR_BLACK);
      init_pair(3, COLOR_GREEN, COLOR_BLACK);
    } else {
      DrawAgain(stats);
    }
    sleepMilli(20);
}

void parseKey(int key, UserAction_t *action, GameInfo_t *stats) {

  switch (key) {
    case 's':
    case 'S':
      if (stats->started) {
        *action = Pause;
      } else
        *action = Start;
      break;
    case 'r':
    case 'R':
      *action = Action;
      break;
    case KEY_DOWN:
      *action = Down;
      break;
    case KEY_LEFT:
      *action = Left;
      break;
    case KEY_RIGHT:
      *action = Right;
      break;
    case KEY_UP:
      *action = Up;
      break;
    case 'Q':
    case 'q':
      *action = Terminate;
      break;
    case 'N':
    case 'n':
      if (stats->stop == 1) {
        (*action = Quit);
      }
      break;
    case 'Y':
    case 'y':
      if (stats->stop == 1) {
        (*action = Again);
      }
      break;
    default:
      *action = Noact;
      break;
  }
}

void drawStartMessage() {
  MVPRINTW(HEIGHT / 2, (WIDTH - INTRO_MESSAGE_LEN) / 2 + 6, INTRO_MESSAGE);
}

void drawRecs(GameInfo_t *stats) {
  printRectangle(0, HEIGHT + 1, 0, HEIGHT + 1);
  printRectangle(0, HEIGHT + 1, HEIGHT + 2, HEIGHT + HUD_WIDTH + 3);

  printRectangle(9, 11, HEIGHT + 3, HEIGHT + HUD_WIDTH + 2);
  printRectangle(12, 15, HEIGHT + 3, HEIGHT + HUD_WIDTH + 2);
  printRectangle(16, 19, HEIGHT + 3, HEIGHT + HUD_WIDTH + 2);

  MVPRINTW(10, HEIGHT + 5, " LEVEL %d", stats->level);
  MVPRINTW(13, HEIGHT + 5, " SCORE");
  MVPRINTW(14, HEIGHT + 5, " %d", stats->score);
  MVPRINTW(17, HEIGHT + 5, "HI_SCORE");
  MVPRINTW(18, HEIGHT + 5, " %d", stats->high_score);
}

void printRectangle(int top_y, int bottom_y, int left_x, int right_x) {
  MVADDCH(top_y, left_x, ACS_ULCORNER);

  int i = left_x + 1;

  for (; i < right_x; i++) MVADDCH(top_y, i, ACS_HLINE);
  MVADDCH(top_y, i, ACS_URCORNER);

  for (int i = top_y + 1; i < bottom_y; i++) {
    MVADDCH(i, left_x, ACS_VLINE);
    MVADDCH(i, right_x, ACS_VLINE);
  }

  MVADDCH(bottom_y, left_x, ACS_LLCORNER);
  i = left_x + 1;
  for (; i < right_x; i++) MVADDCH(bottom_y, i, ACS_HLINE);
  MVADDCH(bottom_y, i, ACS_LRCORNER);
}

void drawField(GameInfo_t *stats) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (stats->field[i][j] == 1) {
        MVADDCH(i + 1, j * 2 + 1, ' ' | A_REVERSE | COLOR_PAIR(1));
        MVADDCH(i + 1, j * 2 + 2, ' ' | A_REVERSE | COLOR_PAIR(1));
      } else if (stats->field[i][j] == 2) {
        MVADDCH(i + 1, j * 2 + 1, ' ' | A_REVERSE | COLOR_PAIR(2));
        MVADDCH(i + 1, j * 2 + 2, ' ' | A_REVERSE | COLOR_PAIR(2));
      }else if (stats->field[i][j] == 3){
        MVADDCH(i + 1, j * 2 + 1, ' ' | A_REVERSE | COLOR_PAIR(3));
        MVADDCH(i + 1, j * 2 + 2, ' ' | A_REVERSE | COLOR_PAIR(3));
      }

      else {
        MVADDCH(i + 1, j * 2 + 1, ' ');
        MVADDCH(i + 1, j * 2 + 2, ' ');
      }
    }
  }
}

void sleepMilli(int milliseconds) {
  struct timespec timer = {0, 0};
  timer.tv_sec = 0;
  timer.tv_nsec = milliseconds * 1000 * 1000;
  nanosleep(&timer, NULL);
}

void DrawNext(GameInfo_t *stats) {
  if (stats->next) {
    printRectangle(1, 8, HEIGHT + 3, HEIGHT + HUD_WIDTH + 2);

    MVPRINTW(2, HEIGHT + 5, " NEXT");

    int start_y = 4;
    int start_x = HEIGHT + 4;
    for (int i = 0; i < CELLS; i++) {
      for (int j = 0; j < CELLS + 1; j++) {
        MVADDCH(i + start_y, j * 2 + start_x, ' ');
        MVADDCH(i + start_y, j * 2 + start_x + 1, ' ');
      }
    }
    for (int i = 0; i < CELLS; i++) {
      MVADDCH(stats->next[i].loc.row + start_y + 1,
              stats->next[i].loc.col * 2 + 1 + start_x,
              ' ' | A_REVERSE | COLOR_PAIR(1));
      MVADDCH(stats->next[i].loc.row + start_y + 1,
              stats->next[i].loc.col * 2 + 2 + start_x,
              ' ' | A_REVERSE | COLOR_PAIR(1));
    }
  }
}

void DrawAgain(GameInfo_t *stats) {
  clear();
  MVPRINTW(HEIGHT / 2 - 3, (WIDTH - (int)strlen(FINAL_MESSAGE_1)) / 2 + 5,
           FINAL_MESSAGE_1);
  MVPRINTW(HEIGHT / 2 - 2, (WIDTH - (int)strlen(FINAL_MESSAGE_2)) / 2 + 5,
           FINAL_MESSAGE_2, stats->score);
  MVPRINTW(HEIGHT / 2 - 1, (WIDTH - (int)strlen(FINAL_MESSAGE_3)) / 2 + 5,
           FINAL_MESSAGE_3, stats->high_score);
  MVPRINTW(HEIGHT / 2, (WIDTH - (int)strlen(FINAL_MESSAGE_4)) / 2 + 5,
           FINAL_MESSAGE_4);
}

void quitNcurses() {
  delwin(stdscr);
  curs_set(0);
  endwin();
  refresh();
}
