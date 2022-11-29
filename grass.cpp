#include "grass.hpp"

Grass::Grass(const sf::Vector2f& size) : Tile(size) {
  this->occupantTower_ = nullptr;
  this->setFillColor(sf::Color(255, 255, 255, 255));
  this->setOutlineThickness(1.f);
  this->setOutlineColor(sf::Color(240, 240, 240, 255));
  this->type_ = 0;
}
Grass::~Grass() { delete occupantTower_; }

void Grass::EmptyTile() {
  delete this->occupantTower_;
  this->occupantTower_ = nullptr;
  this->MakeFree();
}