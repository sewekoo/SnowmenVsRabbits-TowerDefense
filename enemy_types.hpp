#ifndef EASY_ENEMY
#define EASY_ENEMY

#include "enemy.hpp"

// Define enemy type's base stats:
// Easy enemy:
#define EASY_HEALTH 40
#define EASY_SPEED 1
#define EASY_VALUE 10
// Fast enemy:
#define FAST_HEALTH 30
#define FAST_SPEED 2
#define FAST_VALUE 10
// slow enemy:
#define SLOW_HEALTH 100
#define SLOW_SPEED 1
#define SLOW_VALUE 20

/**
 * @brief Derived enemy classes
 *
 * Different type of enemies all decending from the base class "Enemy". The
 * three most basic enemies don't have any special abilities or functions, they
 * just differ in regards to hp, speed and value.
 */

/** \class EasyEnemy
 * @brief Easiest enemy type with low stats
 */
class EasyEnemy : public Enemy {
 public:
  EasyEnemy() : Enemy(EASY_HEALTH, EASY_SPEED, EASY_VALUE, "rabbit_basic.png") {
    this->type_ = 1;
  }

  EasyEnemy(float posX, float posY)
      : Enemy(posX, posY, EASY_HEALTH, EASY_SPEED, EASY_VALUE) {
    this->type_ = 1;
  }
};

/** \class FastEnemy
 * @brief Fast enemy with semi-low HP
 */
class FastEnemy : public Enemy {
 public:
  FastEnemy() : Enemy(FAST_HEALTH, FAST_SPEED, FAST_VALUE, "rabbit_small.png") {
    this->type_ = 2;
  }

  FastEnemy(float posX, float posY)
      : Enemy(posX, posY, FAST_HEALTH, FAST_SPEED, FAST_VALUE) {
    this->type_ = 2;
  }
};

/** \class FastEnemy
 * @brief Slow, tanky enemy with lots of HP
 */
class SlowEnemy : public Enemy {
 public:
  SlowEnemy() : Enemy(SLOW_HEALTH, SLOW_SPEED, SLOW_VALUE, "rabbit_dark.png") {
    this->type_ = 3;
  }

  SlowEnemy(float posX, float posY)
      : Enemy(posX, posY, SLOW_HEALTH, SLOW_SPEED, SLOW_VALUE) {
    this->type_ = 3;
  }
};

#endif