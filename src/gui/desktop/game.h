/**
 * @file game.h
 * @brief Файл содержит объявления структур игры, всех функций backend'а и
 * макросов.
 */
#ifndef GAME_H
#define GAME_H

#include "../../brick_game/snake/controller.h"
#include "../../structures.h"
using namespace s21;
#ifdef TETRIS_DESK
extern "C" {
#include "../../brick_game/tetris/backend.h"
}
#endif

#include <string.h>

#include <QApplication>
#include <QDebug>
#include <QGroupBox>
#include <QKeyEvent>
#include <QLabel>
#include <QMessageBox>
#include <QPainter>
#include <QRectF>
#include <QTime>
#include <QVBoxLayout>
#include <QWidget>

#include "mainwindow.h"

/**
 * @brief Класс виджета игры
 */
class Game : public QWidget {
 private:
  /**
   * @brief Общение с игрой через контроллер
   */
  Controller *controller;
  /**
   * @brief переменная для таймера
   */
  int timerId;

 protected:
  /**
   * @brief перегрузка timerEvent для таймера
   */
  void timerEvent(QTimerEvent *) override;
  /**
   * @brief перегрузка keyPressEvent для вызова при нажатии на клавиатуру
   */
  void keyPressEvent(QKeyEvent *) override;
  /**
   * @brief перегрузка paintEvent для вызова отрисовки
   */
  void paintEvent(QPaintEvent *) override;

 public:
  /**
   * @brief конструктор
   */
  Game(Controller *controller);
  /**
   * @brief деструктор
   */
  ~Game() { deleteGame(); }
  /**
   * @brief удаление всей выделенной памяти
   */
  void deleteGame() {
    for (int i = 0; i < 7; i++) {
      delete labels[i];
    }
    delete again_box;
    delete stats_box;
    delete mainLayout;
  }
  /**
   * @brief парсинг ключей
   */
  void parseKey(int key, UserAction_t *action);
  /**
   * @brief отрисовка прямойгольников
   */
  void drawRecs(QPainter *);
  /**
   * @brief отрисовка змейки/тетрамино
   */
  void drawField(QPainter *);
  /**
   * @brief отрисовка следующей фигура
   */
  void DrawNext(QPainter *);
  /**
   * @brief презапуск игры
   */
  void DrawAgain();
  /**
   * @brief размещение всех надписей
   */
  void set_labels();
  /**
   * @brief получение всех данных об игре
   */
  GameInfo_t *get_stats();
  /**
   * @brief перемеенная заглушка
   */
  bool hold_again;
  /**
   * @brief layout для размещения надписей
   */
  QVBoxLayout *mainLayout;
  /**
   * @brief layout для размещения надписей
   */
  QGroupBox *stats_box;
  /**
   * @brief layout для размещения надписей
   */
  QGroupBox *again_box;
  /**
   * @brief labels
   */
  QLabel *labels[10];
};

#endif  // GAME_H
