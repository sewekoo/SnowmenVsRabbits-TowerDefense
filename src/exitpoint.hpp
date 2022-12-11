#ifndef EXITPOINT_HPP
#define EXITPOINT_HPP
#include "tile.hpp"

class ExitPoint : public Tile {
 public:
  /**
   * @brief Construct a new Exit Point object. Assigns correct type values and colors.
   * 
   * @param size Size of the tile.
   */
  ExitPoint(const sf::Vector2f& size = sf::Vector2f(0, 0));
  /**
   * @brief Destroy the Exit Point object
   * 
   */
  ~ExitPoint();
  /**
   * @brief Set tile status to free and deletes possible occupantEnemy pointer.
   * 
   */
  void EmptyTile();

 private:
};

#endif