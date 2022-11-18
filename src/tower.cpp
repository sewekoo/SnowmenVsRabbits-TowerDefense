#include "tower.hpp"

void Tower::Upgrade() {
    // Increment level
    level_ += 1;

    // Increase value
    value_ += upgradePrice_;

    // Increase damage
    damage_ = 1.5 * damage_;

    // Increase range
    range_ = 1.1 * range_;

    // Increase upgrade price
    upgradePrice_ = 2 * upgradePrice_;

}