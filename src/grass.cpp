#include "grass.hpp"

Grass::Grass(const sf::Vector2f& size) : Tile(size) {
  this->setFillColor(sf::Color(97, 235, 82, 255));
  this->setOutlineThickness(1.f);
  this->setOutlineColor(sf::Color(92, 222, 78, 255));
}
Grass::~Grass() {}

void Grass::EmptyTile() { this->MakeFree(); }