/**
 * @file tetris.h
 * @brief Файл содержит макросы игры
 */
#ifndef TERIS_H
#define TERIS_H

#include "structures.h"
#ifdef TETRIS_CLI
#include <curses.h>
#include <signal.h>

#endif

/**
 * @brief ширина 10 пикселей
 */
#define WIDTH 10

/**
 * @brief высота 20 пикселей
 */
#define HEIGHT 20

/**
 * @brief врменной промежуток 50000
 */
#define TIMESTEP 50000

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

#endif  // S21_TETRIS_H