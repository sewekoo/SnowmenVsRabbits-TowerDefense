#ifndef SNOWBALL_HPP
#define SNOWBALL_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <tuple>
#include <vector>

#include "enemy.hpp"

class Snowball {
 public:
  /**
   * @brief Construct a new Snowball object
   * 
   * @param posX X Coordinate of tile
   * @param posY Y Coordinate of tile
   */
  Snowball(float posX, float posY);
  /**
   * @brief Construct a new Snowball object
   * 
   * @param posX X Coordinate of tile
   * @param posY Y Coordinate of tile
   * @param targetGridX X Coordinate of snowballs target
   * @param targetGridY Y Coordinate of snowballs target
   * @param damage Damage that snowball does to an enemy.
   */
  Snowball(float posX, float posY, int targetGridX, int targetGridY,
           int damage);
  /**
   * @brief Destroy the Snowball object
   */
  ~Snowball();

  int targetType;
  float targetPosX;
  float targetPosY;

  /**
   * @brief Adds specified enemy as target for snowball and calculates landing position.
   * 
   * @param enemy Enemy pointer that snowball targets.
   */
  void AddTarget(Enemy* enemy);

  /**
   * @brief Get the Pos X object
   * 
   * @return float X coordinate of snowball
   */
  float GetPosX();
  /**
   * @brief Get the Pos Y object
   * 
   * @return float Y coordinate of snowball
   */
  float GetPosY();
  /**
   * @brief Get the Target Grid X object
   * 
   * @return int targeted x coordinate
   */
  int GetTargetGridX();
  /**
   * @brief Get the Target Grid Y object
   * 
   * @return int targeted y coordinate
   */
  int GetTargetGridY();
  /**
   * @brief Get the Flight Ticks object
   * 
   * @return int, how many "ticks" snowball has flown
   */
  int GetFlightTicks();
  /**
   * @brief Get the Damage object
   * 
   * @return int damage to be dealt to an enemy
   */
  int GetDamage();

  float initialPosX;
  float initialPosY;

  float flightSpeed;

  float maxFlightX();
  float maxFlightY();

  /**
   * @brief Moves the snowball by specified amount.
   * 
   * @param moveX 
   * @param moveY 
   */
  void move(float moveX, float moveY);

 private:
  float posX_;
  float posY_;
  int targetGridX_;
  int targetGridY_;
  float gridSizeF = 80.f;
  int flightTicks = 0;
  int damage_;
};

#endif