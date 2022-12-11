#ifndef ABSTRACT_ENEMY
#define ABSTRACT_ENEMY

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

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
  Enemy(double hp, float speed, double value, std::string texture)
      : hp_(hp), speed_(speed), value_(value), texture_(texture) {}

  /**
   * Constructor with extra parameters for position in grid
   */
  Enemy(float posX, float posY, double hp, float speed, double value)
      : sf::RectangleShape(sf::Vector2f(gridSizeF, gridSizeF)) {
    posX_ = posX;
    posY_ = posY;
    hp_ = hp;
    speed_ = speed;
    value_ = value;
    this->setSize(sf::Vector2f(gridSizeF, gridSizeF));
    this->setPosition(posX * gridSizeF, posY * gridSizeF);
  }
  /**
   * @brief Destroy the Enemy object
   */
  ~Enemy() {}

  /**
   * @brief TakeDamge takes int as a parameter that tells how much damage is dealt to
   * this enemy. Damage is substracted from hp_. If damage is greater or equal
   * to enemy's hp, it goes to 0. (= enemy dies) Function returns a boolean
   * value indicating if this enemy died during function call.
   * @param dmg Damage to be taken by enemy.
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
  const float GetSpeed() const {
    return speed_;
  } /**< Getter function returns Speed */
  const double GetValue() const {
    return value_;
  } /**< Getter function returns Value */
  const std::string GetTexture() const {
    return texture_;
  } /**< Getter function returns texture */
  /**
   *Getter function
   @return Position x coordinate
  */
  float GetPosX() { return posX_; }
  /**
   *Getter function
   @return Position y coordinate
  */
  float GetPosY() { return posY_; }

  /**
   * @brief Changes enemy pos to new values
   * 
   * @param newPosX New X coordinate
   * @param newPosY New Y coordinate
   */
  void ChangePos(float newPosX, float newPosY) {
    posX_ = newPosX;
    posY_ = newPosY;
  }

  float posX_;
  float posY_;

  /**
   * @brief Get the Grid Pos X object
   * 
   * @return int 
   */
  int GetGridPosX() { return posX_ * gridSizeF; }
  /**
   * @brief Get the Grid Pos Y object
   * 
   * @return int 
   */
  int GetGridPosY() { return posY_ * gridSizeF; }

  int direction = 0;

  int type_;

 private:
  double hp_;
  float speed_;
  double value_;
  std::string texture_;
  float gridSizeF = 80.f;
};

#endif
