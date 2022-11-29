#include "exitpoint.hpp"

ExitPoint::ExitPoint(const sf::Vector2f& size) : Tile(size) {
  this->setFillColor(sf::Color(142, 242, 249, 255));
  this->setOutlineThickness(1.f);
  this->setOutlineColor(sf::Color(142, 242, 249, 255));
  this->type_ = 3;
}
ExitPoint::~ExitPoint() {}

void ExitPoint::EmptyTile() { this->MakeFree(); }