#include "tile.hpp"

Tile::Tile(const sf::Vector2f& size) : sf::RectangleShape(size) {
  next_ = nullptr;
}
Tile::~Tile() { delete next_; }

bool Tile::IsOccupied() { return occupied_; }

void Tile::MakeOccupied() { this->occupied_ = true; }

void Tile::MakeFree() { this->occupied_ = false; }

void Tile::SetNeighbour(Tile* neighbour) { next_ = neighbour; }