#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "enemy_types.hpp"
#include "tower_sniper.hpp"

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

  void SetGridLocation(int x, int y);

  int GetGridLocationX();
  int GetGridLocationY();
  int type_;

  void addOccupant(Tower* tower);
  void addOccupant(Enemy* enemy);

  void removeEnemy();

  Tower* GetTower();
  Enemy* GetEnemy();

  Tower* occupantTower_;
  Enemy* occupantEnemy_;

 private:
  bool occupied_ = false;
  Tile* next_;
  int gridLocationX_;
  int gridLocationY_;
};

#endif