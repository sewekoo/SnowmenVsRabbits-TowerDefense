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
  Snowball(float posX, float posY);
  Snowball(float posX, float posY, int targetGridX, int targetGridY,
           int damage);
  ~Snowball();

  int targetType;
  float targetPosX;
  float targetPosY;

  void CalculateLandPos();
  void AddTarget(Enemy* enemy);

  float GetPosX();
  float GetPosY();
  int GetTargetGridX();
  int GetTargetGridY();
  int GetFlightTicks();
  int GetDamage();

  float initialPosX;
  float initialPosY;

  float flightSpeed;

  float maxFlightX();
  float maxFlightY();

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