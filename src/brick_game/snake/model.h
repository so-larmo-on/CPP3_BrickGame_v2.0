/**
 * @file model.h
 * @brief Файл содержит объявления структур игры, всех функций backend'а и
 * макросов.
 */
#ifndef MODEL_H
#define MODEL_H

#include "../../structures.h"

namespace s21 {

/**
 * @brief Класс модели
 */
class Model {
 public:
  GameInfo_t stats;
  /**
   * @brief Конструктор класса модели
   */
  Model(){};
  /**
   * @brief Деструктор класса модели
   */
  ~Model() = default;
  /**
   * @brief получение данных об игре
   */
  GameInfo_t *getGameInfo_s();
  /**
   * @brief Функция начала игры
   */
  void startGame();
  /**
   * @brief Функция инициализации фигуры
   */
  void initWorm();
  /**
   * @brief Функция сдвига фигуры
   */
  void moveWorm(void);
  /**
   * @brief Функция сдвига фигуры
   */
  void moveWormDir();
  /**
   * @brief Функция выхода из игры из за ошибки
   */
  void errorQuit();
  /**
   * @brief Функция переноса координат фигуры из координат падающей фигуры на
   * поле
   */
  void putFigureOnField();
  /**
   * @brief освобождение памяти
   */
  void freeMap(void);
  /**
   * @brief изменение напрвления
   */
  void changeDirection(UserAction_t direction);
  /**
   * @brief Функция паузы игры
   */
  void pauseGame();
  /**
   * @brief Функция удвления фигуры с поля
   */
  void rmWormFromField();
  /**
   * @brief Функция проверки на движение
   */
  bool mayItGo(int i);
  /**
   * @brief Функция прекращения игры и предложения продолжить либо выйти
   */
  void TerminatePushed();
  /**
   * @brief функция для новог запуска игры
   */
  void playAgain();
  /**
   * @brief Функция получения нужного ускорения в зависимости от уровня
   * @param index индекс уровня
   */
  int getGravity(int index);
  /**
   * @brief расположение еды
   */
  void placeFood();
  /**
   * @brief движение быстрее
   */
  void moveFaster();
  friend class Controller;
};
}  // namespace s21
#endif
