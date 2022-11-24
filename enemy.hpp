#ifndef ABSTRACT_ENEMY
#define ABSTRACT_ENEMY

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

/**
 * \class Enemy
 * @brief An abstract enemy class
 *
 * All enemies have hit points, speed and a sell value (all as int) that depend
 * on the type of enemy in question. A constructor initializes these members and
 * default destructor deletes the class upon destruction.
 */

class Enemy : public sf::RectangleShape {
 public:
  Enemy(float posX, float posY, double hp, double speed, double value)
      : sf::RectangleShape(sf::Vector2f(gridSizeF, gridSizeF)) {
    posX_ = posX;
    posY_ = posY;
    hp_ = hp;
    speed_ = speed;
    value_ = value;
    this->setSize(sf::Vector2f(gridSizeF, gridSizeF));
    this->setPosition(posX * gridSizeF, posY * gridSizeF);
  }

  std::string textureName = "pics/rabbit_basic.png";
  ~Enemy() {}

  /**
   * TakeDamge takes int as a parameter that tells how much damage is dealt to
   * this enemy. Damage is substracted from hp_. If damage is greater or equal
   * to enemy's hp, it goes to 0. (= enemy dies) Function returns a boolean
   * value indicating if this enemy died during function call.
   */
  bool TakeDamage(double dmg) {
    if (hp_ > dmg) {
      hp_ -= dmg;
      return false;
    } else {
      hp_ = 0;
      return true;
    }
  }

  const double GetHP() const { return hp_; } /**< Getter function returns HP */
  const double GetSpeed() const {
    return speed_;
  } /**< Getter function returns Speed */
  const double GetValue() const {
    return value_;
  } /**< Getter function returns Value */

  float GetPosX() { return posX_; }
  float GetPosY() { return posY_; }

  void ChangePos(float newPosX, float newPosY) {
    posX_ = newPosX;
    posY_ = newPosY;
  }

  float posX_;
  float posY_;

  int direction = 0;

 private:
  double hp_;
  double speed_;
  double value_;
  float gridSizeF = 100.f;
  
};

#endif
