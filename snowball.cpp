#include "snowball.hpp"

Snowball::Snowball(float posX, float posY) : posX_(posX), posY_(posY) {
  initialPosX = posX;
  initialPosY = posY;
  flightSpeed = 2.f;
  targetGridX_ = 0;
  targetGridY_ = 0;
  damage_ = 1;
}

Snowball::Snowball(float posX, float posY, int targetGridX, int targetGridY,
                   int damage)
    : posX_(posX),
      posY_(posY),
      targetGridX_(targetGridX),
      targetGridY_(targetGridY),
      damage_(damage) {
  initialPosX = posX;
  initialPosY = posY;
  flightSpeed = 2.f;
}

Snowball::~Snowball() {}

void Snowball::AddTarget(Enemy* enemy) {
  if (enemy->type_ == 1 || enemy->type_ == 3) {
    if (enemy->type_ == 1) {
      this->targetType = 1;
    } else if (enemy->type_ == 3) {
      this->targetType = 3;
    }
    if (enemy->direction == 0) {
      this->targetPosX = (enemy->GetPosX() * gridSizeF) + 60.f;
      this->targetPosY = (enemy->GetPosY() * gridSizeF);
    } else if (enemy->direction == 1) {
      this->targetPosX = (enemy->GetPosX() * gridSizeF);
      this->targetPosY = (enemy->GetPosY() * gridSizeF) + 60.f;
    } else if (enemy->direction == 2) {
      this->targetPosX = (enemy->GetPosX() * gridSizeF) - 60.f;
      this->targetPosY = (enemy->GetPosY() * gridSizeF);
    } else if (enemy->direction == 3) {
      this->targetPosX = (enemy->GetPosX() * gridSizeF);
      this->targetPosY = (enemy->GetPosY() * gridSizeF) - 60.f;
    }
  } else if (enemy->type_ == 2) {
    this->targetType = 2;
    if (enemy->direction == 0) {
      this->targetPosX = (enemy->GetPosX() * gridSizeF) + 100.f;
      this->targetPosY = (enemy->GetPosY() * gridSizeF);
    } else if (enemy->direction == 1) {
      this->targetPosX = (enemy->GetPosX() * gridSizeF);
      this->targetPosY = (enemy->GetPosY() * gridSizeF) + 100.f;
    } else if (enemy->direction == 2) {
      this->targetPosX = (enemy->GetPosX() * gridSizeF) - 100.f;
      this->targetPosY = (enemy->GetPosY() * gridSizeF);
    } else if (enemy->direction == 3) {
      this->targetPosX = (enemy->GetPosX() * gridSizeF);
      this->targetPosY = (enemy->GetPosY() * gridSizeF) - 100.f;
    }
  }
}

float Snowball::GetPosX() { return posX_; }
float Snowball::GetPosY() { return posY_; }
int Snowball::GetFlightTicks() { return flightTicks; }
int Snowball::GetTargetGridX() { return targetGridX_; }
int Snowball::GetTargetGridY() { return targetGridY_; }
int Snowball::GetDamage() { return damage_; }

float Snowball::maxFlightX() {
  return (targetPosX - (this->initialPosX * gridSizeF));
}
float Snowball::maxFlightY() {
  return (targetPosY - (this->initialPosY * gridSizeF));
}

void Snowball::move(float moveX, float moveY) {
  posX_ += moveX / gridSizeF;
  posY_ += moveY / gridSizeF;
  flightTicks++;
}