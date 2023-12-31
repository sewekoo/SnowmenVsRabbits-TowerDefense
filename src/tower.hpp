#ifndef BASE_TOWER
#define BASE_TOWER

#include <iostream>

class Tower {
 public:
  // Constructor
  // TODO: figure out range unit, also coordinate enemy health pool and tower
  // damage
  Tower()
      : damage_(10),
        range_(1),
        attackSpeed_(1.2),
        value_(100),
        upgradePrice_(75),
        level_(1),
        type_("basic") {}

  Tower(double damage, int range, double attackSpeed, double value,
        double upgradePrice, int level, std::string texture, std::string type)
      : damage_(damage),
        range_(range),
        attackSpeed_(attackSpeed),
        value_(value),
        upgradePrice_(upgradePrice),
        level_(level),
        type_(type) {}

  Tower(float posX, float posY, std::string type) {
    if (type == "basic") {
      damage_ = 10;
      range_ = 1;
      attackSpeed_ = 1.2;
      value_ = 100;
      upgradePrice_ = 75;
      level_ = 1;
      type_ = type;
    } else if (type == "hat") {
      damage_ = 10;
      range_ = 1;
      attackSpeed_ = 1.4;
      value_ = 150;
      upgradePrice_ = 125;
      level_ = 1;
      type_ = type;
    } else if (type == "scarf") {
      damage_ = 70;
      range_ = 1;
      attackSpeed_ = 15;
      value_ = 200;
      upgradePrice_ = 175;
      level_ = 1;
      type_ = type;
    }
    posX_ = posX;
    posY_ = posY;
  }

  // Destructor
  ~Tower() {}

  // Getter functions
  const double GetDamage() { return damage_; }
  const int GetRange() { return range_; }
  const double GetSpeed() { return attackSpeed_; }
  const double GetValue() { return value_; }
  const double GetUpgradePrice() { return upgradePrice_; }
  const int GetLevel() { return level_; }
  const std::string& GetType() { return type_; }
  float GetGridPosX() { return posX_ * gridSizeF; }
  float GetGridPosY() { return posY_ * gridSizeF; }

  // Upgrade is different for different towers
  virtual void Upgrade();

  // Refund should maybe be a function in the game object same as buy. It can
  // use GetValue to know how much to refund.

  float posX_;
  float posY_;

  double CooldownValue = 0;
  bool ReadyToFire = true;

  float targetPosX;
  float targetPosY;
  bool hasTarget = false;

 protected:
  double damage_;
  int range_;
  double attackSpeed_;
  double value_;
  double upgradePrice_;
  int level_;
  float gridSizeF = 80.f;
  std::string type_;
};

#endif