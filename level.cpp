#include "level.hpp"

Level::Level(const int mapSize, std::vector<std::vector<std::string>> levelInfo,
             float gridSizeF)
    : mapSize_(mapSize), levelInfo_(levelInfo), gridSizeF_(gridSizeF) {
  this->initializeLevel();
}

Level::Level(const int mapSize, std::vector<std::vector<std::string>> levelInfo,
             std::vector<std::tuple<std::tuple<int, int>, std::tuple<int, int>>>
                 neighbourInfo,
             float gridSizeF)
    : mapSize_(mapSize),
      levelInfo_(levelInfo),
      neighbourInfo_(neighbourInfo),
      gridSizeF_(gridSizeF) {
  this->initializeLevel();
  this->initalizeNeighbours();
}

Level::~Level() {}

int Level::GetMapSize() { return mapSize_; }

void Level::initializeLevel() {
  for (int x = 0; x < this->mapSize_; x++) {
    tileMap.resize(mapSize_, std::vector<Tile>());
    for (int y = 0; y < this->mapSize_; y++) {
      tileMap[x].resize(mapSize_, Tile());
      tileMap[x][y].setSize(sf::Vector2f(gridSizeF_, gridSizeF_));

      try {
        if (this->levelInfo_[x][y] ==
            "0") {  // If info points to grass, then fill with grass
          tileMap[x][y] = Grass(sf::Vector2f(gridSizeF_, gridSizeF_));
        } else if (this->levelInfo_[x][y] ==
                   "1") {  // If info points to road, then fill with road
          tileMap[x][y] = Road(sf::Vector2f(gridSizeF_, gridSizeF_));
        } else if (this->levelInfo_[x][y] ==
                   "2") {  // If info points to entry point, then make it entry
                           // point
          EntryPoint newEntryPoint =
              EntryPoint(sf::Vector2f(gridSizeF_, gridSizeF_));
          tileMap[x][y] = newEntryPoint;
          entrypoint = newEntryPoint;
          entrypoint.setPosition(x * gridSizeF_, y * gridSizeF_);
        } else if (this->levelInfo_[x][y] ==
                   "3") {  // If info points to exit point, then make it exit
                           // point
          ExitPoint newExitPoint =
              ExitPoint(sf::Vector2f(gridSizeF_, gridSizeF_));
          tileMap[x][y] = newExitPoint;
          exitpoint = newExitPoint;
          exitpoint.setPosition(x * gridSizeF_, y * gridSizeF_);
        } else {
          tileMap[x][y] = Grass(sf::Vector2f(gridSizeF_, gridSizeF_));
        }
      } catch (const std::exception& e) {  // If no info in levelInfo variable,
                                           // then fill with grass
        tileMap[x][y] = Grass(sf::Vector2f(gridSizeF_, gridSizeF_));
      }
      tileMap[x][y].setPosition(x * gridSizeF_, y * gridSizeF_);
    }
  }
}

void Level::initalizeNeighbours() {
  for (auto i : this->neighbourInfo_) {
    std::tuple<int, int> coordFirst = std::get<0>(i);
    std::tuple<int, int> coordSecond = std::get<1>(i);
    tileMap[std::get<0>(coordFirst)][std::get<1>(coordFirst)].SetNeighbour(
        &tileMap[std::get<0>(coordSecond)][std::get<1>(coordSecond)]);
  }
}