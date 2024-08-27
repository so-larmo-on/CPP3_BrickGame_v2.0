/**
 * @file structures.h
 * @brief Файл содержит объявления структур игры
 */
#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <time.h>

/**
 * @brief ширина поля
 */
#define WIDTH 10

/**
 * @brief высота поля
 */
#define HEIGHT 20

/**
 * @brief шаг для таймера
 */
#define TIMESTEP 50000

/**
 * @brief кол-во ориентаций фигуры
 */
#define ORI 4

/**
 * @brief кол-во блоков змейки
 */
#define WORMSIZE 4
/**
 * @brief кол-во блоков фигуры
 */
#define CELLS 4

/**
 * @brief все возможные действия пользователя
 */
typedef enum UserAction_t {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
  Quit,
  Again,
  Noact
} UserAction_t;

/**
 * @brief Структура, описывающая тетрамино
 * @param x x
 * @param y y
 *
 */
struct worm_part {
  int x;
  int y;
};
/**
 * @brief Структура, содержащая пару чисел - строчка и столбец
 */
typedef struct Tlocation {
  int row;
  int col;
} Tlocation;

/**
 * @brief Структура, описывающая тетрамино
 * @param type Тип тетрамино
 * @param orintation Ориентация
 * @param loc Структура столбца и строчки каждого блока
 */
typedef struct Tblock {
  int type;
  int orintation;
  Tlocation loc;
} Tblock;

/**
 * @brief Структура, содержащая показатели игры
 * @param field поле
 * @param score очки
 * @param high_score рекорд
 * @param level уровень
 * @param pause пауза
 * @param started заглушка
 * @param falling падающая фигура
 * @param next следующая фигура
 * @param ticks скорость
 * @param UserAction_t направление;
 * @param action действие
 * @param worm координаты частей червя
 * @param length длина
 */
typedef struct GameInfo_t {
  int **field;
  int score;
  int high_score;
  int level;
  int pause;
  int started;
  int ticks;
  int stop;
  int length;
  int faster;
  Tblock *next;
  Tblock *falling;
  UserAction_t dir;
  UserAction_t action;
  struct worm_part *worm;

} GameInfo_t;

#endif