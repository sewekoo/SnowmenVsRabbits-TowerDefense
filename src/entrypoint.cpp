#include "entrypoint.hpp"

EntryPoint::EntryPoint(const sf::Vector2f& size) : Tile(size) {
  this->setFillColor(sf::Color(40, 40, 40, 255));
  this->setOutlineThickness(15.f);
  this->setOutlineColor(sf::Color(141, 141, 141, 255));
  this->type_ = 2;
}
EntryPoint::~EntryPoint() {}

void EntryPoint::EmptyTile() { this->MakeFree(); }