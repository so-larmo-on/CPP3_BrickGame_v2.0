/**
 * @file backend.h
 * @brief Файл содержит объявления всех функций backend'а тетриса и
 * макросов.
 */
#ifndef BACKEND_H
#define BACKEND_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <time.h>

#include "../../structures.h"

#ifdef TETRIS_CLI
#include "../../gui/cli/cview.h"
#endif
/**
 * @brief кол-во фигур
 */
#define TETRAMINOS 7

/**
 * @brief кол-во ориентаций фигуры
 */
#define ORI 4

/**
 * @brief кол-во блоков фигуры
 */
#define CELLS 4

/**
 * @brief Функция выделения памяти под главную структуру игры
 */
GameInfo_t *getGameInfo_t();

/**
 * @brief Функция, определяющая следующее действие в зависимости от ввода
 * пользователя
 * @param action действие игрока
 * @param hold заглушка
 */
void userInput(UserAction_t action, int hold);

/**
 * @brief Функция начала игры
 */
void startGame();

void gameLoop();

/**
 * @brief Функция инициализации фигуры
 */
void initFigure();

/**
 * @brief Функция установки таймера
 */
void setTimer(void);

/**
 * @brief Функция устанвки сигналов
 */
void setSignals(void);

/**
 * @brief Функция, определяющая следующее действие в зависимости от полученного
 * сигнала
 */
void handler(int signum);

/**
 * @brief Функция сдвига фигуры вниз на 1 блок
 */
void moveDown(void);

/**
 * @brief Функция выхода из игры по выбору пользователя
 */
void quit();

/**
 * @brief Функция экстренного выхода из игры
 * @param msg сообщение об ошибке
 */
void errorQuit(char *msg);

/**
 * @brief Функция переноса координат фигуры из координат падающей фигуры на поле
 */
void putFigureOnField();

/**
 * @brief Функция чистки памяти
 */
void freeMap(void);

/**
 * @brief Функция проверки на движение вниз
 */
int mayItGoDown();

/**
 * @brief Функция движения фигуры вправо/влево
 */
void moveFigure(UserAction_t direction);

/**
 * @brief Функция паузы игры
 */
void pauseGame();

/**
 * @brief Функция поворота фигуры
 */
void rotateFigure();

/**
 * @brief Функция получения координат в зависимоси от типа и ориентации фигуры
 * @param tetramino тип фигуры
 * @param orientation ориентация фигуры
 * @param cells блок фигуры
 */
Tlocation getTetr(int tetramino, int orintation, int cells);

/**
 * @brief Функция удвления фигуры с поля
 */
void rmTetraminoFromField();

/**
 * @brief Функция проверки на поворот фигуры
 */
int mayItRotate();

/**
 * @brief Функция движения налево
 */
void moveLeft();

/**
 * @brief Функция движения направо
 */
void moveRight();

/**
 * @brief Функция удаления строк
 */
void deleteLines();

/**
 * @brief Функция проверки на заполненность строки поля
 * @param i индекс строки поля
 */
int fullLine(int i);

/**
 * @brief Функция возведения в степень двойки
 * @param degree степень двойки
 */
int fastPow(int degree);

/**
 * @brief Функция прекращения игры и предложения продолжить либо выйти
 */
void TerminatePushed();

/**
 * @brief Функция вызова новой игры
 */
void playAgain();

/**
 * @brief Функция получения нынешних показателей игры
 */
GameInfo_t *updateCurrentState_t();

/**
 * @brief Функция получения нужного ускорения в зависимости от уровня
 * @param index индекс уровня
 */
int getGravity(int index);

/**
 * @brief Функция инициализации игры
 */
int initGame();

#endif  // S21_TETRIS_H