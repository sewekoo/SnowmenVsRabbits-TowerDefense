#include "road.hpp"

Road::Road(const sf::Vector2f& size) : Tile(size) {
  this->InitalizeColors();
  // occupant_ = nullptr;
  // next_ = nullptr;
}

/**
Road::Road(Road* next, const sf::Vector2f& size) : Tile(size) {
  this->InitalizeColors();
  // occupant_ = nullptr;
  next_ = next;
}
*/

Road::~Road() {
  // delete occupant_;
  // delete next_;
}

void Road::InitalizeColors() {
  this->setFillColor(sf::Color(223, 189, 110, 255));
  this->setOutlineThickness(1.f);
  this->setOutlineColor(sf::Color(213, 181, 104, 255));
}

// Road& Road::GetNext() { return *next_; }

// void Road::SetNext(Road* next) { next_ = next; }

/**
void Road::AddEnemy(Enemy* enemy) {
   this->occupant_ = enemy;
  this->MakeOccupied();
}
*/

void Road::EmptyTile() {
  // delete this->occupant_;
  // this->occupant_ = nullptr;
  this->MakeFree();
}