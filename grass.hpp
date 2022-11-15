#ifndef GRASS_HPP
#define GRASS_HPP
#include "tile.hpp"

class Grass : public Tile {
 public:
  Grass(const sf::Vector2f& size = sf::Vector2f(0, 0));
  ~Grass();

  void EmptyTile();

 private:
  // TODO: ADD TOWER OCCUPANT AND MAKE NECESSARY METHODS
};

#endif