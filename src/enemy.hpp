#ifndef ABSTRACT_ENEMY
#define ABSTRACT_ENEMY


#include <iostream>

/** 
 * \class Enemy
 * @brief An abstract enemy class
 * 
 * All enemies have hit points, speed and a sell value (all as int) that depend on the type of enemy in question.
 * A constructor initializes these members and default destructor deletes the class upon destruction.
 */

class Enemy {
public:
  Enemy(int hp, int speed, int value) : hp_(hp), speed_(speed), value_(value) { }
  ~Enemy();

  /**
   * TakeDamge takes int as a parameter that tells how much damage is dealt to this enemy.
   * Damage is substracted from hp_. If damage is greater or equal to enemy's hp, it goes to 0. (= enemy dies)
   * Function returns a boolean value indicating if this enemy died during function call.
   */
  bool TakeDamage(int dmg) {
    if (hp_ > dmg) {
      hp_ -= dmg;
      return false;
    } else {
      hp_ = 0;
      return true;
    }
  }

  const int GetHP() const { return hp_; }         /**< Getter function returns HP */
  const int GetSpeed() const { return speed_; }   /**< Getter function returns Speed */
  const int GetValue() const { return value_; }   /**< Getter function returns Value */

private:
  int hp_;
  int speed_;
  int value_;

};

#endif
