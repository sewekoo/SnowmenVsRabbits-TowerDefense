#include "tile.hpp"

Tile::Tile(const sf::Vector2f& size) : sf::RectangleShape(size) {
  next_ = nullptr;
  occupantEnemy_ = nullptr;
  occupantTower_ = nullptr;
}

Tile::~Tile() {
  delete next_;
  delete occupantEnemy_;
  delete occupantTower_;
}

bool Tile::IsOccupied() { return occupied_; }

void Tile::MakeOccupied() { this->occupied_ = true; }

void Tile::MakeFree() { this->occupied_ = false; }

void Tile::SetNeighbour(Tile* neighbour) { next_ = neighbour; }

void Tile::SetGridLocation(int x, int y) {
  gridLocationX_ = x;
  gridLocationY_ = y;
}

int Tile::GetGridLocationX() { return gridLocationX_; }

int Tile::GetGridLocationY() { return gridLocationY_; }

void Tile::addOccupant(Tower* tower) { occupantTower_ = tower; }

void Tile::addOccupant(Enemy* enemy) { occupantEnemy_ = enemy; }

Enemy* Tile::GetEnemy() { return occupantEnemy_; }

Tower* Tile::GetTower() { return occupantTower_; }