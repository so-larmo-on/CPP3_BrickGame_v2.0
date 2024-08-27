/**
 * @file controller.h
 * @brief Файл содержит объявления структур игры, всех функций backend'а и
 * макросов.
 */
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../../structures.h"
#include "model.h"

namespace s21 {
/**
 * @brief класс Контроллера
 */
class Controller {
 private:
  Model *model;

 public:
  /**
   * @brief Конструктор
   */
  Controller(Model *m) : model(m){};
  /**
   * @brief Деструктор
   */
  ~Controller() = default;
  /**
   * @brief получение данных об игре
   */
  GameInfo_t *updateCurrentState();
  /**
   * @brief Функция игрового цикла
   */
  void gameLoop_c();
  /**
   * @brief Функция начала игры
   */
  void startGame_c();
  /**
   * @brief Функция ввода действия пользователя
   */
  void userInput(UserAction_t action, bool hold);
  /**
   * @brief Функция паузы
   */
  void pauseGame_c();
  /**
   * @brief Функция изменения напрваленияы
   */
  void changeDirection_c(UserAction_t action);
  /**
   * @brief Функция прекращения игры и предложения продолжить либо выйти
   */
  void TerminatePushed_c();
  /**
   * @brief Функция движения
   */
  void moveWorm_c();
  /**
   * @brief Функция получения нужного ускорения в зависимости от уровня
   * @param grav индекс уровня
   */
  int getGravity_c(int grav);
  /**
   * @brief Функция движения быстрее
   */
  void moveFaster_c();
  /**
   * @brief Функция выхода
   */
  void quit();
};
}  // namespace s21
#endif
