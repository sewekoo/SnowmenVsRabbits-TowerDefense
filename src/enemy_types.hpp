#ifndef EASY_ENEMY
#define EASY_ENEMY

#include "enemy.hpp"


// Define enemy type's base stats:
// Easy enemy:
#define EASY_HEALTH 30
#define EASY_SPEED 10
#define EASY_VALUE 10
// Fast enemy:
#define FAST_HEALTH 25
#define FAST_SPEED 20
#define FAST_VALUE 10
// slow enemy:
#define SLOW_HEALTH 50
#define SLOW_SPEED 5
#define SLOW_VALUE 20

/**
 * @brief Derived enemy classes
 * 
 * Different type of enemies all decending from the base class "Enemy". The three most basic enemies
 * don't have any special abilities or functions, they just differ in regards to hp, speed and value.
 */

/** \class EasyEnemy
 * @brief Easiest enemy type with low stats
 */ 
class EasyEnemy : public Enemy {
public:
    EasyEnemy() : Enemy(EASY_HEALTH, EASY_SPEED, EASY_VALUE, "rabbit_basic.png") { }
};

/** \class FastEnemy
 * @brief Fast enemy with semi-low HP
 */
class FastEnemy : public Enemy {
public:
    FastEnemy() : Enemy(FAST_HEALTH, FAST_SPEED, FAST_VALUE, "rabbit_small.png") { }
};

/** \class FastEnemy
 * @brief Slow, tanky enemy with lots of HP
 */
class SlowEnemy : public Enemy {
public:
    SlowEnemy() : Enemy(SLOW_HEALTH, SLOW_SPEED, SLOW_VALUE, "rabbit_dark.png") { }
};


#endif