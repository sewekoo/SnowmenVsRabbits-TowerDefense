#ifndef EXITPOINT_HPP
#define EXITPOINT_HPP
#include "tile.hpp"

class ExitPoint : public Tile {
 public:
  ExitPoint(const sf::Vector2f& size = sf::Vector2f(0, 0));
  ~ExitPoint();

  void EmptyTile();

 private:
  // TODO: ADD TOWER OCCUPANT AND MAKE NECESSARY METHODS
};

#endif