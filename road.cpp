#include "road.hpp"

Road::Road(const sf::Vector2f& size) : Tile(size) {
  this->InitalizeColors();
}

Road::~Road() { }

void Road::InitalizeColors() {
  this->setFillColor(sf::Color(223, 189, 110, 255));
  this->setOutlineThickness(1.f);
  this->setOutlineColor(sf::Color(213, 181, 104, 255));
  this->type_ = 1;
}

void Road::EmptyTile() {
  this->MakeFree();
}