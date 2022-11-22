#include "road.hpp"

Road::Road(const sf::Vector2f& size) : Tile(size) {
  this->InitalizeColors();
  this->occupantEnemy_ = nullptr;
}

Road::~Road() { delete occupantEnemy_; }

void Road::InitalizeColors() {
  this->setFillColor(sf::Color(223, 189, 110, 255));
  this->setOutlineThickness(1.f);
  this->setOutlineColor(sf::Color(213, 181, 104, 255));
  this->type_ = 1;
}

void Road::EmptyTile() {
  delete this->occupantEnemy_;
  this->occupantEnemy_ = nullptr;
  this->MakeFree();
}