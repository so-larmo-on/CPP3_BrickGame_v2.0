#include "game.h"

#include "../../brick_game/snake/controller.h"
using namespace s21;
#ifdef TETRIS_DESK
extern "C" {
#include "../../brick_game/tetris/backend.h"
}
#endif
using namespace s21;

GameInfo_t *Game::get_stats() {
  GameInfo_t *stats;
#ifdef SNAKE_DESK
  stats = controller->updateCurrentState();

#endif
#ifdef TETRIS_DESK
  stats = updateCurrentState_t();

#endif
  return stats;
}

Game::Game(Controller *controller) : controller(controller) {
  GameInfo_t *stats = get_stats();
  this->resize(HEIGHT * WIDTH * 2 - 19, HEIGHT * WIDTH * 2 + 18);
  this->setWindowTitle("game");
  set_labels();
  this->show();

  this->hold_again = true;

  timerId = startTimer(50);
};

void Game::set_labels() {
  GameInfo_t *stats = get_stats();
  mainLayout = new QVBoxLayout(this);
  QGridLayout *layout = new QGridLayout;
  stats_box = new QGroupBox();
  stats_box->setFlat(true);
  stats_box->setStyleSheet("QGroupBox#theBox {border:0;}");
  mainLayout->addWidget(stats_box);
  for (int i = 1; i < 4; ++i) {  // stats
    labels[i] = new QLabel();
    labels[i]->hide();
  }
  labels[7] = new QLabel();
  labels[7]->hide();
  layout->addWidget(labels[1], 2, 2, 5, 2, Qt::AlignTop);
  layout->addWidget(labels[2], 3, 2, 5, 2, Qt::AlignTop);
  layout->addWidget(labels[3], 4, 2, 5, 2, Qt::AlignTop);
  layout->addWidget(labels[7], 5, 2, 5, 2, Qt::AlignTop);
  layout->setColumnStretch(1, 10);
  stats_box->setLayout(layout);
  stats_box->hide();

  QGridLayout *layout1 = new QGridLayout;
  again_box = new QGroupBox();
  again_box->setFlat(true);
  again_box->setStyleSheet("QGroupBox#theBox {border:0;}");
  mainLayout->addWidget(again_box);  //
  for (int i = 4; i < 7; ++i) {
    labels[i] = new QLabel();

    labels[i]->hide();
  }
  layout1->addWidget(labels[4], 1, 1, 5, 2);
  layout1->addWidget(labels[5], 2, 1, 5, 2);
  layout1->addWidget(labels[6], 3, 1, 5, 2);

  layout1->setColumnStretch(1, 10);
  again_box->setLayout(layout1);
  again_box->hide();
  labels[0] = new QLabel("to start press s");
  mainLayout->addWidget(labels[0]);
  for (int i = 0; i < 7; i++) {
    labels[i]->show();
  }
}
void Game::DrawAgain() {
  GameInfo_t *stats = get_stats();
  if (this->hold_again) {
    labels[1]->hide();
    labels[2]->hide();
    labels[3]->hide();
    if (stats->next) {
      labels[7]->hide();
    }
    stats_box->hide();
    this->hold_again = false;

    labels[4]->setText(tr("your level is %1").arg(stats->level));
    labels[4]->show();

    labels[5]->setText(tr("your score is %1").arg(stats->score));
    labels[5]->show();

    labels[6]->setText(tr("your high score is %1").arg(stats->high_score));
    labels[6]->show();
    again_box->show();
  }
}

void Game::drawRecs(QPainter *qp) {
  GameInfo_t *stats = get_stats();
  if (!stats->stop) {
    qp->drawRect(1, 1, 213, 413);
    qp->drawRect(220, 1, 140, 413);
    labels[1]->setText(tr("level %1").arg(stats->level));  // str
    labels[1]->show();

    labels[2]->setText(tr("score %1").arg(stats->score));
    labels[2]->show();

    labels[3]->setText(tr("hi_score %1").arg(stats->high_score));
    labels[3]->show();

    if (stats->next) {
      labels[7]->setText(tr("next"));
      labels[7]->show();
      qp->drawRect(260, 160, 90, 90);
    }
    qp->drawRect(260, 25, 90, 30);
    qp->drawRect(260, 70, 90, 30);
    qp->drawRect(260, 115, 90, 30);
  }
}

void Game::drawField(QPainter *qp) {
  GameInfo_t *stats = get_stats();
  if (!stats->stop) {
    for (int i = 0; i < HEIGHT; i++) {
      for (int j = 0; j < WIDTH; j++) {
        if (stats->field[i][j] == 1) {
          qp->setBrush(Qt::darkMagenta);
          qp->drawRect(j * 20 + 10, i * 20 + 10, 20, 20);
        } else if (stats->field[i][j] == 2) {
          qp->setBrush(Qt::darkBlue);
          qp->drawRect(j * 20 + 10, i * 20 + 10, 20, 20);
        } else if (stats->field[i][j] == 3) {
          qp->setBrush(Qt::darkGreen);
          qp->drawRect(j * 20 + 10, i * 20 + 10, 20, 20);
        }
      }
    }
  }
}
void Game::DrawNext(QPainter *qp) {
  GameInfo_t *stats = get_stats();
  if (stats->next) {
    for (int i = 0; i < CELLS; i++) {
      qp->setBrush(Qt::darkMagenta);
      qp->drawRect(stats->next[i].loc.col * 20 + 270,
                   stats->next[i].loc.row * 20 + 185, 20, 20);
    }
  }
}

void Game::timerEvent(QTimerEvent *e) {
  Q_UNUSED(e);

  GameInfo_t *stats = get_stats();

  if (stats->started && !stats->stop) {
    if (!labels[0]->isHidden()) {
      labels[0]->hide();
    }
    if (!labels[4]->isHidden()) {
      hold_again = true;
      labels[4]->hide();
      labels[5]->hide();
      labels[6]->hide();
      again_box->hide();
    }
    if (stats_box->isHidden()) {
      labels[1]->show();
      labels[2]->show();
      labels[3]->show();
      if (stats->next) {
        labels[7]->show();
      }
      stats_box->show();
    }

#ifdef SNAKE_DESK
    controller->gameLoop_c();
#endif
#ifdef TETRIS_DESK
    gameLoop();
#endif

    update();
  } else if (stats->stop) {
    update();
    Game::DrawAgain();
  }
}

void Game::parseKey(int key, UserAction_t *action) {
  GameInfo_t *stats = get_stats();
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
    case Qt::Key_Down:
      *action = Down;
      break;
    case Qt::Key_Left:
      *action = Left;
      break;
    case Qt::Key_Right:
      *action = Right;
      break;
    case Qt::Key_Up:
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
        *action = Again;
      }
      break;
    default:
      *action = Noact;
      break;
  }
}

void Game::keyPressEvent(QKeyEvent *e) {
  GameInfo_t *stats = get_stats();
  bool hold = stats->started;
  int key = e->key();
  UserAction_t action;
  parseKey(key, &action);
  stats->action = action;
#ifdef SNAKE_DESK
  controller->userInput(action, hold);
#endif
#ifdef TETRIS_DESK
  userInput(action, hold);

#endif
}

void Game::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e);
  GameInfo_t *stats = get_stats();
  QPainter qp(this);
  if (stats->started && !stats->stop) {
    Game::drawRecs(&qp);

    Game::drawField(&qp);
    Game::DrawNext(&qp);
  }
}
