#ifndef SNIPER_TOWER
#define SNIPER_TOWER

#include <iostream>
#include "tower.hpp"

class Sniper : public Tower {
    public:
    Sniper() : Tower(100, 500, 0.33, 200, 150, 1, "snowman_hat.png") {}

    virtual void Upgrade();
    
};


#endif