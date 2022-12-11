#ifndef GRASS_HPP
#define GRASS_HPP
#include "tile.hpp"

class Grass : public Tile {
 public:
  /**
   * @brief Construct a new Grass object. Assigns correct type value & correct color
   * 
   * @param size Size of the tile.
   */
  Grass(const sf::Vector2f& size = sf::Vector2f(0, 0));
  /**
   * @brief Destroy the Grass object
   * 
   */
  ~Grass();
  /**
   * @brief Deletes possible tower occupant and sets tile status to free.
   * 
   */
  void EmptyTile();

 private:
};

#endif