#ifndef ROAD_HPP
#define ROAD_HPP

#include "tile.hpp"

class Road : public Tile {
 public:
  Road(const sf::Vector2f& size = sf::Vector2f(0, 0));

  Road(Road* next, const sf::Vector2f& size = sf::Vector2f(0, 0));

  ~Road();

  void InitalizeColors();

  void EmptyTile();
  // void AddEnemy(Enemy* enemy);

  // void SetNext(Road* next);

  // Road& GetNext();

 private:
  // Enemy* occupant_;
  // Road* next_;
};

#endif