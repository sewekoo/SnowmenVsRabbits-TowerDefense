#include "entrypoint.hpp"

EntryPoint::EntryPoint(const sf::Vector2f& size) : Tile(size) {
  this->setFillColor(sf::Color(142, 242, 249, 255));
  this->setOutlineThickness(1.f);
  this->setOutlineColor(sf::Color(142, 242, 249, 255));
  this->type_ = 2;
}
EntryPoint::~EntryPoint() {}

void EntryPoint::EmptyTile() { this->MakeFree(); }