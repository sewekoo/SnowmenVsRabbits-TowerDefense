#ifndef ENTRYPOINT_HPP
#define ENTRYPOINT_HPP
#include "tile.hpp"

class EntryPoint : public Tile {
 public:
 /**
  * @brief Construct a new Entry Point object. Assigns correct type value and colors.
  * 
  * @param size Size of the tile.
  */
  EntryPoint(const sf::Vector2f& size = sf::Vector2f(0, 0));
  /**
   * @brief Destroy the Entry Point object
   * 
   */
  ~EntryPoint();
  /**
   * @brief Makes the tile empty and deletes possible enemy occupant.
   * 
   */
  void EmptyTile();

 private:
};

#endif