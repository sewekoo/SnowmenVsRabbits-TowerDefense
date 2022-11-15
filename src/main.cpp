#include <iostream>

#include "game.hpp"

int main() {
  // Initalizes game class
  Game game;
  // Runs the game while window is open
  while (game.GetWindowIsOpen()) {
    game.update();
    game.render();
  }

  return 0;
}