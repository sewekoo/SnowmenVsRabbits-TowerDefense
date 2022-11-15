#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "enemy.hpp"

/**
 * Abstract class to represent one tile in a level.
 * Inherits SFML RectangleShape class.
 */
class Tile : public sf::RectangleShape {
 public:
  /**
   * Constructor
   */
  Tile(const sf::Vector2f& size = sf::Vector2f(0, 0));

  /**
   * Destructor
   */
  ~Tile();

  /**
   * @return True if occupied. False if not.
   * May be occupied by either enemy or tower.
   */
  bool IsOccupied();

  void MakeOccupied();
  void MakeFree();

  void SetNeighbour(Tile* neighbour);

 private:
  bool occupied_ = false;
  Tile* next_;
};

#endif