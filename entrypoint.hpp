#ifndef ENTRYPOINT_HPP
#define ENTRYPOINT_HPP
#include "tile.hpp"

class EntryPoint : public Tile {
 public:
  EntryPoint(const sf::Vector2f& size = sf::Vector2f(0, 0));
  ~EntryPoint();

  void EmptyTile();

 private:
  // TODO: ADD TOWER OCCUPANT AND MAKE NECESSARY METHODS
};

#endif