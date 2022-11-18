#include "tower.hpp"
#include "tower_sniper.hpp"


int main() {
    Tower t1;

    for(size_t i = 0; i<5; i++) {
        std::cout << "Level: " << t1.GetLevel() << std::endl;
        std::cout << "Damage: " << t1.GetDamage()
                << " Range: " << t1.GetRange()
                << " Speed: " << t1.GetSpeed()
                << " Value: " << t1.GetValue()
                << " Texture: " << t1.GetTexture()
                << " Upgrade price: " << t1.GetUpgradePrice() << std::endl;

        t1.Upgrade();
    }

    std::cout << "Creating a sniper tower" << std::endl;

    Sniper t2;

    for(size_t i = 0; i<5; i++) {
        std::cout << "Level: " << t2.GetLevel() << std::endl;
        std::cout << "Damage: " << t2.GetDamage()
                << " Range: " << t2.GetRange()
                << " Speed: " << t2.GetSpeed()
                << " Value: " << t2.GetValue()
                << " Texture: " << t2.GetTexture()
                << " Upgrade price: " << t2.GetUpgradePrice() << std::endl;

        t2.Upgrade();
    }


    return 1;
}