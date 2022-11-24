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

      try {
        if (this->levelInfo_[x][y] ==
            "0") {  // If info points to grass, then fill with grass
          tileMap[x][y] = Grass(sf::Vector2f(gridSizeF_, gridSizeF_));
        } else if (this->levelInfo_[x][y] ==
                   "1") {  // If info points to road, then fill with road
          Road newRoad = Road(sf::Vector2f(gridSizeF_, gridSizeF_));
          tileMap[x][y] = newRoad;
          roads.push_back(newRoad);
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

      tileMap[x][y].setSize(sf::Vector2f(gridSizeF_, gridSizeF_));
      tileMap[x][y].setPosition(x * gridSizeF_, y * gridSizeF_);
      std::cout << "Tile set to position " << tileMap[x][y].getPosition().x
                << " " << tileMap[x][y].getPosition().y << std::endl;
      tileMap[x][y].SetGridLocation(x, y);
      std::cout << "Saved position " << x << " " << y << std::endl;
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

void Level::TurnEnemies() {
  for (int x = 0; x < GetMapSize(); x++) {
    for (int y = 0; y < GetMapSize(); y++) {
      if(tileMap[x][y].IsOccupied() && tileMap[x][y].type_ == 1) {
        if(tileMap[x][y].GetGridLocationX() < tileMap[x][y].GetNext()->GetGridLocationX()) {
         tileMap[x][y].GetEnemy()->direction = 0;
         //std::cout << "Set direction to right" << std::endl;
        } else if(tileMap[x][y].GetGridLocationX() > tileMap[x][y].GetNext()->GetGridLocationX()) {
          tileMap[x][y].GetEnemy()->direction = 2;
          //std::cout << "Set direction to left." << std::endl;
          //std::cout << "Enemy x pos: " << (static_cast<unsigned>((tileMap[x][y].GetEnemy()->GetPosX()))) << std::endl;
          //std::cout << "Next x pos: " << (static_cast<unsigned>((tileMap[x][y].GetNext()->GetGridLocationX()))) << std::endl;
        } else if(tileMap[x][y].GetGridLocationY() < tileMap[x][y].GetNext()->GetGridLocationY()) {
          tileMap[x][y].GetEnemy()->direction = 1;
          //std::cout << "Set direction to down" << std::endl;
        } else if(tileMap[x][y].GetGridLocationY() > tileMap[x][y].GetNext()->GetGridLocationY()) {
          tileMap[x][y].GetEnemy()->direction = 3;
          //std::cout << "Set direction to up" << std::endl;
        }
      }
    }
  }  
}

void Level::MoveEnemies() {
  for (int x = 0; x < GetMapSize(); x++) {
    for (int y = 0; y < GetMapSize(); y++) {
      if (tileMap[x][y].type_ == 1 && 
          tileMap[x][y].IsOccupied() &&
          tileMap[x][y].GetEnemy()->direction == 0 &&
          !tileMap[x][y].GetNext()->IsOccupied() &&
          (tileMap[x][y].GetEnemy()->GetPosX() != tileMap[x][y].GetNext()->GetGridLocationX() * 1.f ||
          tileMap[x][y].GetEnemy()->GetPosY() != tileMap[x][y].GetNext()->GetGridLocationY() * 1.f)
          ) {
        tileMap[x][y].GetEnemy()->ChangePos(tileMap[x][y].GetEnemy()->GetPosX() + (1.f / 100.f), tileMap[x][y].GetEnemy()->GetPosY());
      } else if (tileMap[x][y].type_ == 1 && 
          tileMap[x][y].IsOccupied() &&
          tileMap[x][y].GetEnemy()->direction == 1 &&
          !tileMap[x][y].GetNext()->IsOccupied() &&
          (tileMap[x][y].GetEnemy()->GetPosX() != tileMap[x][y].GetNext()->GetGridLocationX() * 1.f ||
          tileMap[x][y].GetEnemy()->GetPosY() != tileMap[x][y].GetNext()->GetGridLocationY() * 1.f)
          ) {
        //std::cout << "EnemyPos: " << tileMap[x][y].GetEnemy()->GetPosX() << "  " << tileMap[x][y].GetEnemy()->GetPosY() << std::endl;
        //std::cout << "Next tile Pos: " << tileMap[x][y].GetNext()->GetGridLocationX() << "  " << tileMap[x][y].GetNext()->GetGridLocationY() << std::endl;
        //std::cout << (tileMap[x][y].GetEnemy()->GetPosX() != tileMap[x][y].GetNext()->GetGridLocationX()) * 1.f << std::endl;
        tileMap[x][y].GetEnemy()->ChangePos(tileMap[x][y].GetEnemy()->GetPosX(), tileMap[x][y].GetEnemy()->GetPosY() + (1.f / 100.f));
      } else if (tileMap[x][y].type_ == 1 &&
          tileMap[x][y].IsOccupied() &&
          tileMap[x][y].GetEnemy()->direction == 2 &&
          !tileMap[x][y].GetNext()->IsOccupied() &&
          (tileMap[x][y].GetEnemy()->GetPosX() != tileMap[x][y].GetNext()->GetGridLocationX() * 1.f ||
          tileMap[x][y].GetEnemy()->GetPosY() != tileMap[x][y].GetNext()->GetGridLocationY() * 1.f)
          ) {
        //std::cout << "Enemy x pos: " << (static_cast<double>((tileMap[x][y].GetEnemy()->GetPosX()))) << std::endl;
        //std::cout << "Next x pos: " << (static_cast<double>((tileMap[x][y].GetNext()->GetGridLocationX()))) << std::endl;
        //std::cout << "Left pixel movement" << std::endl;
        tileMap[x][y].GetEnemy()->ChangePos(static_cast<float>(tileMap[x][y].GetEnemy()->GetPosX()) - (1.f / 100), tileMap[x][y].GetEnemy()->GetPosY());
        //std::cout << "Enemy x pos: " << (static_cast<double>((tileMap[x][y].GetEnemy()->GetPosX()))) << std::endl;
        //std::cout << "Next x pos: " << (static_cast<double>((tileMap[x][y].GetNext()->GetGridLocationX()))) << std::endl;
        
      } else if (tileMap[x][y].type_ == 1 && 
          tileMap[x][y].IsOccupied() &&
          tileMap[x][y].GetEnemy()->direction == 3 &&
          !tileMap[x][y].GetNext()->IsOccupied() &&
          (tileMap[x][y].GetEnemy()->GetPosX() != tileMap[x][y].GetNext()->GetGridLocationX() * 1.f ||
          tileMap[x][y].GetEnemy()->GetPosY() != tileMap[x][y].GetNext()->GetGridLocationY() * 1.f)
          ) {
        tileMap[x][y].GetEnemy()->ChangePos(tileMap[x][y].GetEnemy()->GetPosX(), tileMap[x][y].GetEnemy()->GetPosY() - (1.f / 100));
      }
      if (tileMap[x][y].type_ == 1) {
        //std::cout << "Type check: " << (tileMap[x][y].type_ == 1) << std::endl;
        if (tileMap[x][y].IsOccupied()) {
          //std::cout << "Tile occupied test: " << (tileMap[x][y].IsOccupied()) << std::endl;
          //std::cout << "Enemy mover flag test: " << (tileMap[x][y].enemyMovedHere) << std::endl;
          //std::cout << "Next not occupied test: " << (!tileMap[x][y].GetNext()->IsOccupied()) << std::endl;
          //std::cout << "Same X pos test: " << (static_cast<double>(tileMap[x][y].GetEnemy()->GetPosX()) == static_cast<double>(tileMap[x][y].GetNext()->GetGridLocationX() * 1.f)) << std::endl;
          //std::cout << "Same Y pos test: " << (static_cast<double>(tileMap[x][y].GetEnemy()->GetPosY() * 1.f) == static_cast<double>(tileMap[x][y].GetNext()->GetGridLocationY() * 1.f)) << std::endl;
        }
      }



      if (tileMap[x][y].type_ == 1 && 
          tileMap[x][y].IsOccupied() && 
          tileMap[x][y].enemyMovedHere && 
          !tileMap[x][y].GetNext()->IsOccupied() &&
          ((static_cast<double>(tileMap[x][y].GetEnemy()->GetPosX()) > static_cast<double>(tileMap[x][y].GetNext()->GetGridLocationX()) &&
          (tileMap[x][y].GetEnemy()->direction == 0)) 
          ||
          (static_cast<double>(tileMap[x][y].GetEnemy()->GetPosY()) > static_cast<double>(tileMap[x][y].GetNext()->GetGridLocationY()) &&
          (tileMap[x][y].GetEnemy()->direction == 1)
          )
          ||
          (static_cast<double>(tileMap[x][y].GetEnemy()->GetPosX()) < static_cast<double>(tileMap[x][y].GetNext()->GetGridLocationX()) &&
          (tileMap[x][y].GetEnemy()->direction == 2)) 
          ||
          (static_cast<double>(tileMap[x][y].GetEnemy()->GetPosY()) < static_cast<double>(tileMap[x][y].GetNext()->GetGridLocationY()) &&
          (tileMap[x][y].GetEnemy()->direction == 3))
          )) {
        //std::cout << "Enemy x pos: " << (static_cast<double>((tileMap[x][y].GetEnemy()->GetPosX()))) << std::endl;
        //std::cout << "Next x pos: " << (static_cast<double>((tileMap[x][y].GetNext()->GetGridLocationX()))) << std::endl;
        //std::cout << "move one enemy" << std::endl;
        //std::cout << tileMap[x][y].GetEnemy() << std::endl;
        tileMap[x][y].GetNext()->addOccupant(tileMap[x][y].GetEnemy());
        //std::cout << tileMap[x][y].GetNext()->GetEnemy() << std::endl;
        //std::cout << "Successfully added enemy pointer to next" << std::endl;
        tileMap[x][y].GetNext()->MakeOccupied();
        //std::cout << "Successfully made next tile occupied" << std::endl;
        tileMap[x][y].GetNext()->enemyMovedHere = false;
        //std::cout << "Succesfully turned enemyMovedFlag to false" << std::endl;
        // tileMap[x][y].GetEnemy()->ChangePos(tileMap[x][y].GetNext()->GetGridLocationX(), tileMap[x][y].GetNext()->GetGridLocationY());
        // std::cout << "Successfully changed Pos values in enemy instance" << std::endl;
        tileMap[x][y].enemyMoved();
        //std::cout << "Successfully removed enemy pointer from current tile" << std::endl;
      }
    }
  }
  for (int x = 0; x < GetMapSize(); x++) {
    for (int y = 0; y < GetMapSize(); y++) {
      tileMap[x][y].enemyMovedHere = true;
    }
  }
}