#include <gtest/gtest.h>
#include <string.h>
#include "../brick_game/snake/controller.h"
#include "../brick_game/snake/model.h"
#include <cstdio>
#include <iostream>
#include <ctime>
#include <iostream>
#include <random>
#include <string.h>

#include <fstream>
#include <signal.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <time.h>
using namespace s21;

// TEST (Snake, constructor_default) {
//   Model model;
//   Controller controller(&model);
//    controller.userInput(Quit, 0);
// }



TEST(Snake1, Start1) {
  s21::Model model;
  s21::Controller controller(&model);
  controller.userInput(Start, 0);
  controller.userInput(Terminate, 1);
  controller.userInput(Quit, 0);
  
}

TEST(Snake2, Moves) {
  s21::Model model;
  s21::Controller controller(&model);
  controller.userInput(Start, 0);
  controller.userInput(Down, 1);
  controller.userInput(Left, 1);
  controller.userInput(Up, 1);
  controller.userInput(Right, 1);
  controller.userInput(Pause, 1);
  controller.userInput(Pause, 0);
  controller.userInput(Terminate, 1);
  controller.userInput(Quit, 0);

  
}

TEST(Snake3, GameLoop) {
  s21::Model model;
  s21::Controller controller(&model);
  controller.startGame_c();
  controller.gameLoop_c();
  GameInfo_t *stats = controller.updateCurrentState();
  EXPECT_EQ(stats->started, 1);
  
  controller.moveWorm_c();
  controller.moveFaster_c();
  controller.changeDirection_c(Down);
  controller.userInput(Action, 1);
  
  stats->ticks = 27;
  stats->level = 1;
  stats->pause = 0;
  stats->stop = 0;
  controller.gameLoop_c(); 
  controller.getGravity_c(1);
  controller.userInput(Again, 1);
  controller.TerminatePushed_c();
  controller.userInput(Quit, 0);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}