#ifndef BASE_TOWER
#define BASE_TOWER

#include <iostream>

class Tower {
    public:
    // Constructor
    // TODO: figure out range unit, also coordinate enemy health pool and tower damage
    Tower() : damage_(20), range_(50), attackSpeed_(1.2), value_(100), upgradePrice_(75), level_(1) {}

    // Destructor
    ~Tower();

    // Getter functions
    const double GetDamage() { return damage_; }
    const double GetRange() { return range_; }
    const double GetSpeed() { return attackSpeed_; }
    const double GetValue() { return value_; }
    const double GetUpgradePrice() { return upgradePrice_; }
    const int GetLevel() { return level_; }

    // Upgrade is different for different towers
    virtual void Upgrade();

    // Refund should maybe be a function in the game object same as buy. It can use GetValue to know
    // how much to refund.

    private:
    double damage_;
    double range_;
    double attackSpeed_;
    double value_;
    double upgradePrice_;
    int level_;
};

#endif