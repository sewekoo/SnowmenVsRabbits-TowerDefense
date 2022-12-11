#ifndef ROAD_HPP
#define ROAD_HPP

#include "tile.hpp"

class Road : public Tile {
 public:
  /**
   * @brief Construct a new Road object. Assigns correct tile value and colors.
   * 
   * @param size Size of the tile.
   */
  Road(const sf::Vector2f& size = sf::Vector2f(0, 0));
  /**
   * @brief Destroy the Road object
   * 
   */
  ~Road();
  /**
   * @brief Initializes correct colors
   * 
   */
  void InitalizeColors();
  /**
   * @brief Sets tile status to free and destroys possible enemy pointer.
   * 
   */
  void EmptyTile();
  /**
   * @brief Adds enemy pointer to tile.
   * 
   * @param enemy Enemy pointer to be added.
   */
  void AddEnemy(Enemy* enemy);

 private:
};

#endif