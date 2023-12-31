#include "game.hpp"

// Constructors
Game::Game() {
  this->InitializeVariables();
  this->InitializeWindow();
  this->InitializeView();
  this->InitializeLevel();
}

Game::Game(int mapsize, std::vector<std::vector<std::string>> levelTiles,
           std::vector<std::tuple<std::tuple<int, int>, std::tuple<int, int>>>
               neighbourInfo) {
  this->InitializeVariables();
  this->InitializeWindow();
  this->InitializeView();
  this->level = new Level(mapsize, levelTiles, neighbourInfo, gridSizeF);
}

Game::Game(int mapsize, std::vector<std::vector<std::string>> levelTiles,
           std::vector<std::tuple<std::tuple<int, int>, std::tuple<int, int>>>
               neighbourInfo,
           std::vector<std::vector<int>> enemyInfo) {
  this->InitializeVariables();
  this->InitializeWindow();
  this->InitializeView();
  this->level =
      new Level(mapsize, levelTiles, neighbourInfo, gridSizeF, enemyInfo);
}

// Destructors
Game::~Game() {
  delete this->window;
  delete this->level;
  for (auto i : towers) {
    delete i;
  }
  for (auto i : snowballs) {
    delete i;
  }
}

// Functions

// Accessor to get Window status
const bool Game::GetWindowIsOpen() const { return this->window->isOpen(); }

// Update functions, split between functionalities

// Polls all events (for example closing window)
void Game::pollEvents() {
  while (this->window->pollEvent(event)) {
    switch (this->event.type) {
      case sf::Event::Closed:
        this->window->close();
        break;

      case sf::Event::KeyPressed:
        if (this->event.key.code == sf::Keyboard::Escape) {
          this->window->close();
        }
        break;
      case sf::Event::MouseButtonPressed:
        if (sidebar.MouseOnButton(*(this->window), sidebar.GetTower1B())) {
          basic_clicked = true;
          hat_clicked = false;
          scarf_clicked = false;
          clickSelection = 1;
          std::cout << "1B pressed" << std::endl;
        } else if (sidebar.MouseOnButton(*(this->window),
                                         sidebar.GetTower2B())) {
          basic_clicked = false;
          hat_clicked = true;
          scarf_clicked = false;
          clickSelection = 2;
          std::cout << "2B pressed" << std::endl;
        } else if (sidebar.MouseOnButton(*(this->window),
                                         sidebar.GetTower3B())) {
          basic_clicked = false;
          hat_clicked = false;
          scarf_clicked = true;
          clickSelection = 3;
          std::cout << "3B pressed" << std::endl;
        } else if (sidebar.MouseOnButton(*(this->window),
                                         sidebar.GetGoButton())) {
          go_clicked = true;
        }
        break;
    }
  }
}

// Updates users input. May be necessary to implement some inputs in future.
void Game::updateInput() {
  if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    mouseClicked = false;
  }
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseClicked == false) {
    mouseClicked = true;
    std::cout << "Left Mouse clicked" << std::endl;
    for (int x = 0; x < this->level->GetMapSize(); x++) {
      for (int y = 0; y < this->level->GetMapSize(); y++) {
        if ((this->level->tileMap[x][y].IsOccupied()) &&
            (this->level->tileMap[x][y].type_ == 0) &&
            (this->level->tileMap[x][y].GetGridLocationX() == mousePosGrid.x) &&
            (this->level->tileMap[x][y].GetGridLocationY() == mousePosGrid.y)) {
          if (this->wallet >=
              this->level->tileMap[x][y].GetTower()->GetUpgradePrice()) {
            if (this->level->tileMap[x][y].GetTower()->GetLevel() < 2) {
              std::cout << "Tower upgrade sequence began" << std::endl;
              if (this->level->tileMap[x][y].GetTower() != nullptr) {
                std::cout
                    << "Tile tower value is not nullptr. Trying to upgrade:"
                    << std::endl;
                try {
                  std::cout
                      << this->level->tileMap[x][y].occupantTower_ << "level: "
                      << this->level->tileMap[x][y].occupantTower_->GetLevel()
                      << std::endl;
                  wallet -=
                      this->level->tileMap[x][y].GetTower()->GetUpgradePrice();
                  this->level->tileMap[x][y].occupantTower_->Upgrade();
                  std::cout
                      << "Upgrade success. New level: "
                      << this->level->tileMap[x][y].occupantTower_->GetLevel()
                      << std::endl;
                } catch (const std::exception& e) {
                  std::cout << "Upgrade failed" << std::endl;
                }
              }
            } else {
              latestMessage = "Max level";
            }
          } else {
            latestMessage = "Not enough money.";
          }
        }
        /**
                if ((this->level->tileMap[x][y].IsOccupied()) &&
                    (this->level->tileMap[x][y].type_ == 1) &&
                    (this->level->tileMap[x][y].GetGridLocationX() ==
           mousePosGrid.x) && (this->level->tileMap[x][y].GetGridLocationY() ==
           mousePosGrid.y)) { if
           (this->level->tileMap[x][y].GetEnemy()->TakeDamage(10)) { auto size =
           enemies.size(); for (int i = 0; i != size; i++) { if
           (enemies[i]->GetHP() <= 0) { enemies.erase(enemies.begin() + i);
                      }
                    }
                    this->wallet +=
           this->level->tileMap[x][y].GetEnemy()->GetValue();
                    this->level->tileMap[x][y].removeEnemy();
                    enemyDestroyedThisTick = false;
                    std::cout << "Enemy is killed" << std::endl;
                  } else {
                    std::cout << "Enemy hp: "
                              << this->level->tileMap[x][y].GetEnemy()->GetHP()
                              << std::endl;
                  }

                  std::cout << "Enemy hp: "
                            << this->level->tileMap[x][y].GetEnemy()->GetHP()
                            << std::endl;
                }

                if ((!this->level->tileMap[x][y].IsOccupied()) &&
                    ((this->level->tileMap[x][y].type_ == 1) ||
                     (this->level->tileMap[x][y].type_ == 2)) &&
                    (this->level->tileMap[x][y].GetGridLocationX() ==
           mousePosGrid.x) && (this->level->tileMap[x][y].GetGridLocationY() ==
           mousePosGrid.y) && (this->enemyDestroyedThisTick)) { std::cout <<
           "MousePos X & Y: " << mousePosGrid.x << " "
                            << mousePosGrid.y << std::endl;
                  std::cout << "TilePos X & Y: "
                            << this->level->tileMap[x][y].GetGridLocationX() <<
           " "
                            << this->level->tileMap[x][y].GetGridLocationY()
                            << std::endl;
                  std::cout << "Enemy adding sequence began" << std::endl;
                  Enemy* newEnemy =
                      new EasyEnemy(this->mousePosGrid.x, this->mousePosGrid.y);
                  std::cout << "Enemy created into variable succesful" <<
           std::endl; enemies.push_back(newEnemy); std::cout << "Enemy pushed to
           enemies vector succesful" << std::endl;
                  this->level->tileMap[x][y].addOccupant(newEnemy);
                  enemiesAdded++;
                  this->level->tileMap[x][y].MakeOccupied();
                  std::cout << "Succesfully increased enemy counter" <<
           std::endl;
                }
        */
        else if ((!this->level->tileMap[x][y].IsOccupied()) &&
                 (this->level->tileMap[x][y].type_ == 0) &&
                 (this->level->tileMap[x][y].GetGridLocationX() ==
                  mousePosGrid.x) &&
                 (this->level->tileMap[x][y].GetGridLocationY() ==
                  mousePosGrid.y) &&
                 (basic_clicked == true)) {
          if (this->wallet >= 100.0) {
            Tower* newTower =
                new Tower(this->mousePosGrid.x, this->mousePosGrid.y, "basic");
            towers.push_back(newTower);
            this->level->tileMap[x][y].addOccupant(newTower);
            this->level->tileMap[x][y].MakeOccupied();
            this->wallet -= 100;
          } else {
            latestMessage = "Not enough money";
          }
          basic_clicked = false;
          hat_clicked = false;
          scarf_clicked = false;
          clickSelection = 0;
        }

        else if ((!this->level->tileMap[x][y].IsOccupied()) &&
                 (this->level->tileMap[x][y].type_ == 0) &&
                 (this->level->tileMap[x][y].GetGridLocationX() ==
                  mousePosGrid.x) &&
                 (this->level->tileMap[x][y].GetGridLocationY() ==
                  mousePosGrid.y) &&
                 (hat_clicked == true)) {
          if (this->wallet >= 150.0) {
            Tower* newTower =
                new Tower(this->mousePosGrid.x, this->mousePosGrid.y, "hat");
            towers.push_back(newTower);
            this->level->tileMap[x][y].addOccupant(newTower);
            this->level->tileMap[x][y].MakeOccupied();
            this->wallet -= 150;
          } else {
            latestMessage = "Not enough money";
          }
          basic_clicked = false;
          hat_clicked = false;
          scarf_clicked = false;
          clickSelection = 0;
        }

        else if ((!this->level->tileMap[x][y].IsOccupied()) &&
                 (this->level->tileMap[x][y].type_ == 0) &&
                 (this->level->tileMap[x][y].GetGridLocationX() ==
                  mousePosGrid.x) &&
                 (this->level->tileMap[x][y].GetGridLocationY() ==
                  mousePosGrid.y) &&
                 (scarf_clicked == true)) {
          if (this->wallet >= 200.0) {
            Tower* newTower =
                new Tower(this->mousePosGrid.x, this->mousePosGrid.y, "scarf");
            towers.push_back(newTower);
            this->level->tileMap[x][y].addOccupant(newTower);
            this->level->tileMap[x][y].MakeOccupied();
            this->wallet -= 200;
          } else {
            latestMessage = "Not enough money";
          }
          basic_clicked = false;
          hat_clicked = false;
          scarf_clicked = false;
          clickSelection = 0;
        }
      }
    }
  } else if (sf::Mouse::isButtonPressed(
                 sf::Mouse::Right)) {  // Removal of tower
    std::cout << "Right Mouse clicked" << std::endl;
    for (int x = 0; x < this->level->GetMapSize(); x++) {
      for (int y = 0; y < this->level->GetMapSize(); y++) {
        if ((this->level->tileMap[x][y].IsOccupied()) &&
            (this->level->tileMap[x][y].type_ == 0) &&
            (this->level->tileMap[x][y].GetGridLocationX() == mousePosGrid.x) &&
            (this->level->tileMap[x][y].GetGridLocationY() == mousePosGrid.y)) {
          for (auto i : towers) {
            if (i->GetGridPosX() == this->mousePosGrid.x * gridSizeF &&
                i->GetGridPosY() == this->mousePosGrid.y * gridSizeF) {
              if ((*i).GetType() == "basic") {
                this->wallet += 50;
              } else if ((*i).GetType() == "hat") {
                this->wallet += 75;
              } else if ((*i).GetType() == "scarf") {
                this->wallet += 100;
              }
              towers.erase(std::remove(towers.begin(), towers.end(), i),
                           towers.end());
              this->level->tileMap[x][y].MakeFree();
              std::cout << "tower removed" << std::endl;
            }
          }
        }
      }
    }
  }
  enemyDestroyedThisTick = true;
}

/**
 * @brief Fires all of the towers that are not on cooldown at enemies in range
 *
 */
void Game::FireTowers() {
  for (int x = 0; x < this->level->GetMapSize(); x++) {
    for (int y = 0; y < this->level->GetMapSize(); y++) {
      if (this->level->tileMap[x][y].type_ == 0 &&
          this->level->tileMap[x][y].IsOccupied()) {
        if (!this->level->tileMap[x][y].GetTower()->ReadyToFire) {
          this->level->tileMap[x][y].GetTower()->CooldownValue += 0.1;
          if (this->level->tileMap[x][y].GetTower()->CooldownValue >=
              this->level->tileMap[x][y].GetTower()->GetSpeed()) {
            this->level->tileMap[x][y].GetTower()->CooldownValue = 0;
            this->level->tileMap[x][y].GetTower()->ReadyToFire = true;
          }
        }
        for (int z = 0; z < this->level->GetMapSize(); z++) {
          for (int q = 0; q < this->level->GetMapSize(); q++) {
            if (this->level->tileMap[z][q].type_ == 1 &&
                this->level->tileMap[z][q].IsOccupied()) {
              if ((((this->level->tileMap[x][y].GetGridLocationX() -
                         this->level->tileMap[z][q].GetGridLocationX() <=
                     this->level->tileMap[x][y].GetTower()->GetRange()) &&
                    (this->level->tileMap[x][y].GetGridLocationX() -
                         this->level->tileMap[z][q].GetGridLocationX() >=
                     0)) ||
                   ((this->level->tileMap[x][y].GetGridLocationX() -
                         this->level->tileMap[z][q].GetGridLocationX() >=
                     (-1 *
                      this->level->tileMap[x][y].GetTower()->GetRange())) &&
                    (this->level->tileMap[x][y].GetGridLocationX() -
                         this->level->tileMap[z][q].GetGridLocationX() <
                     0))) &&
                  (((this->level->tileMap[x][y].GetGridLocationY() -
                         this->level->tileMap[z][q].GetGridLocationY() <=
                     this->level->tileMap[x][y].GetTower()->GetRange()) &&
                    (this->level->tileMap[x][y].GetGridLocationY() -
                         this->level->tileMap[z][q].GetGridLocationY() >=
                     0)) ||
                   ((this->level->tileMap[x][y].GetGridLocationY() -
                         this->level->tileMap[z][q].GetGridLocationY() >=
                     (-1 *
                      this->level->tileMap[x][y].GetTower()->GetRange())) &&
                    (this->level->tileMap[x][y].GetGridLocationY() -
                         this->level->tileMap[z][q].GetGridLocationY() <
                     0)))) {
                this->level->tileMap[x][y].GetTower()->targetPosX =
                    this->level->tileMap[z][q].GetEnemy()->posX_;
                this->level->tileMap[x][y].GetTower()->targetPosY =
                    this->level->tileMap[z][q].GetEnemy()->posY_;
                this->level->tileMap[x][y].GetTower()->hasTarget = true;
                if (this->level->tileMap[x][y].GetTower()->ReadyToFire) {
                  spawnSnowball(
                      this->level->tileMap[x][y].GetTower()->posX_,
                      this->level->tileMap[x][y].GetTower()->posY_,
                      this->level->tileMap[z][q].GetEnemy(),
                      this->level->tileMap[z][q].GetGridLocationX(),
                      this->level->tileMap[z][q].GetGridLocationY(),
                      this->level->tileMap[x][y].GetTower()->GetDamage());
                  this->level->tileMap[x][y].GetTower()->ReadyToFire = false;
                }
              }
            }
          }
        }
      }
    }
  }
}

void Game::spawnSnowball(float posX, float posY, Enemy* enemy, int targetGridX,
                         int targetGridY, int damage) {
  Snowball* newSnowball =
      new Snowball(posX, posY, targetGridX, targetGridY, damage);
  // std::cout << "New snowball at pos: " << posX << " " << posY << std::endl;
  // std::cout << "Target pos at: " << targetGridX << " " << targetGridY
  //<< std::endl;
  newSnowball->AddTarget(enemy);
  snowballs.push_back(newSnowball);
}

void Game::updateSnowballs() {
  int flightLength = 30;
  for (auto ball : snowballs) {
    // std::cout << "Ball targetPosX: " << ball->targetPosX << std::endl;
    // std::cout << "Ball initialPosX: " << ball->initialPosX << std::endl;
    // std::cout << "Ball maxFlightX: " << ball->maxFlightX() << std::endl;
    // std::cout << "Ball moved from " << ball->GetPosX() << " "
    //  << ball->GetPosY();
    ball->move(ball->maxFlightX() / flightLength,
               ball->maxFlightY() / flightLength);
    // std::cout << " to: " << ball->GetPosX() << " " << ball->GetPosY()
    //       << std::endl;
    if (ball->GetFlightTicks() >= flightLength) {
      if (this->level->tileMap[ball->GetTargetGridX()][ball->GetTargetGridY()]
              .IsOccupied() &&
          this->level->tileMap[ball->GetTargetGridX()][ball->GetTargetGridY()]
                  .type_ == 1) {
        if (this->level->tileMap[ball->GetTargetGridX()][ball->GetTargetGridY()]
                .GetEnemy()
                ->TakeDamage(ball->GetDamage())) {
          auto size = enemies.size();
          for (int i = 0; i != size; i++) {
            if (enemies[i]->GetHP() <= 0) {
              enemies.erase(enemies.begin() + i);
            }
          }
          this->wallet +=
              this->level
                  ->tileMap[ball->GetTargetGridX()][ball->GetTargetGridY()]
                  .GetEnemy()
                  ->GetValue();
          this->level->tileMap[ball->GetTargetGridX()][ball->GetTargetGridY()]
              .removeEnemy();
          // std::cout << "Enemy is killed" << std::endl;
        } else {
          // std::cout
          //<< "Enemy hp: "
          //<< this->level
          //      ->tileMap[ball->GetTargetGridX()][ball->GetTargetGridY()]
          //      .GetEnemy()
          //       ->GetHP()
          //<< std::endl;
        }
      } else if (this->level
                     ->tileMap[ball->GetTargetGridX()][ball->GetTargetGridY()]
                     .GetNext()
                     ->IsOccupied() &&
                 this->level
                         ->tileMap[ball->GetTargetGridX()]
                                  [ball->GetTargetGridY()]
                         .GetNext()
                         ->type_ == 1) {
        if (this->level->tileMap[ball->GetTargetGridX()][ball->GetTargetGridY()]
                .GetNext()
                ->GetEnemy()
                ->TakeDamage(ball->GetDamage())) {
          auto size = enemies.size();
          for (int i = 0; i != size; i++) {
            if (enemies[i]->GetHP() <= 0) {
              enemies.erase(enemies.begin() + i);
            }
          }
          this->wallet +=
              this->level
                  ->tileMap[ball->GetTargetGridX()][ball->GetTargetGridY()]
                  .GetNext()
                  ->GetEnemy()
                  ->GetValue();
          this->level->tileMap[ball->GetTargetGridX()][ball->GetTargetGridY()]
              .GetNext()
              ->removeEnemy();
          // std::cout << "Enemy is killed" << std::endl;
        } else {
          // std::cout
          //    << "Enemy hp: "
          //    << this->level
          //          ->tileMap[ball->GetTargetGridX()][ball->GetTargetGridY()]
          //          .GetNext()
          //           ->GetEnemy()
          //            ->GetHP()
          //   << std::endl;
        }
      }
      auto size = snowballs.size();
      for (int i = 0; i != size; i++) {
        if (snowballs[i]->GetFlightTicks() >= flightLength) {
          Snowball* it = snowballs.at(i);
          delete it;
          snowballs.erase(snowballs.begin() + i);
        }
      }
    }
  }
}

void Game::spawnEnemies() {
  for (int x = 0; x < this->level->GetMapSize(); x++) {
    for (int y = 0; y < this->level->GetMapSize(); y++) {
      if (this->level->tileMap[x][y].type_ == 2 &&
          !this->level->tileMap[x][y].IsOccupied()) {
        // std::cout << "Enemy adding sequence began" << std::endl;
        int nextEnemyType = this->level->SpawnNext();
        Enemy* newEnemy;
        if (nextEnemyType == 1) {
          newEnemy =
              new EasyEnemy(this->level->tileMap[x][y].GetGridLocationX(),
                            this->level->tileMap[x][y].GetGridLocationY());
        } else if (nextEnemyType == 2) {
          newEnemy =
              new FastEnemy(this->level->tileMap[x][y].GetGridLocationX(),
                            this->level->tileMap[x][y].GetGridLocationY());
        } else if (nextEnemyType == 3) {
          newEnemy =
              new SlowEnemy(this->level->tileMap[x][y].GetGridLocationX(),
                            this->level->tileMap[x][y].GetGridLocationY());
        } else if (nextEnemyType == 0) {
          if (enemies.empty()) {
            if (this->level->EndRound()) {
              latestMessage = "Level won!";
              this->gameState = 2;
            } else {
              this->BuildClock.restart();
              if (round < 2) {
                this->wallet += 100 - (round * 20);
              } else {
                this->wallet += 10;
              }
              this->round += 1;
              this->gameState = 0;
            }
          }
        }
        if (nextEnemyType != 0) {
          // std::cout << "Enemy created into variable succesful" << std::endl;
          enemies.push_back(newEnemy);
          // std::cout << "Enemy pushed to enemies vector succesful" <<
          // std::endl;
          this->level->tileMap[x][y].addOccupant(newEnemy);
          enemiesAdded++;
          this->level->tileMap[x][y].MakeOccupied();
          // std::cout << "Succesfully increased enemy counter" << std::endl;
        }
      }
    }
  }
}

/**
 * @brief Updates tower firing clock.
 * Change fireTime variable to change all towers' fire rate
 */
void ::Game::updateFireClock() {
  sf::Time timeElapsed = FireClock.getElapsedTime();
  sf::Int64 fireTime = 60000;
  if (timeElapsed.asMicroseconds() >= fireTime) {
    if (!this->level->LevelLost) {
      FireClock.restart();
      FireTowers();
    } else {
      gameState = 3;
      latestMessage = "Level lost.";
    }
  }
}

void Game::updateSnowballClock() {
  sf::Time timeElapsed = SnowballClock.getElapsedTime();
  sf::Int64 snowballSpeed = 10000;
  if (timeElapsed.asMicroseconds() >= snowballSpeed) {
    SnowballClock.restart();
    updateSnowballs();
  }
}

void Game::updateBuildClock() {
  sf::Time timeElapsed = SpawnClock.getElapsedTime();
  float buildingTime = 15;
  if ((timeElapsed.asSeconds() >= buildingTime && gameState == 0) ||
      (go_clicked == true && gameState == 0)) {
    SpawnClock.restart();
    this->level->ConfigureRound();
    gameState = 1;
    go_clicked = false;
  }
}

void Game::updateSpawnClock() {
  sf::Time timeElapsed = SpawnClock.getElapsedTime();
  sf::Int32 spawnTime = 1500;
  if (timeElapsed.asMilliseconds() >= spawnTime && gameState == 1) {
    SpawnClock.restart();
    this->spawnEnemies();
  }
}

/**
 * @brief Enemy movement clock
 * Change moveTime variable to change all enemies speed
 * (bigger = slower)
 */
void Game::updateMoveClock() {
  sf::Time timeElapsed = MoveClock.getElapsedTime();
  sf::Int64 moveTime = 6000;
  if (timeElapsed.asMicroseconds() >= moveTime) {
    if (!this->level->LevelLost) {
      MoveClock.restart();
      // std::cout << "Move enemies" << std::endl;
      this->level->TurnEnemies();
      this->level->MoveEnemies();
    }
  }
}

// Tracks mouse movement
void Game::updateMousePosition() {
  mousePosScreen.x = sf::Mouse::getPosition().x;
  mousePosScreen.y = sf::Mouse::getPosition().y;
  mousePosWindow.x = sf::Mouse::getPosition(*window).x;
  mousePosWindow.y = sf::Mouse::getPosition(*window).y;
  this->window->setView(view);
  mousePosView.x = this->window->mapPixelToCoords(mousePosWindow).x;
  mousePosView.y = this->window->mapPixelToCoords(mousePosWindow).y;
  if (mousePosView.x >= 0.f) {
    mousePosGrid.x = mousePosWindow.x / gridSizeU;
  }
  if (mousePosView.y >= 0.f) {
    mousePosGrid.y = mousePosWindow.y / gridSizeU;
  }
  this->window->setView(this->window->getDefaultView());

  std::stringstream ss;
  ss << "Screen: x: " << mousePosScreen.x << " y: " << mousePosScreen.y
     << std::endl;
  ss << "Window: x: " << mousePosWindow.x << " y: " << mousePosWindow.y
     << std::endl;
  ss << "View: x: " << mousePosView.x << " y: " << mousePosView.y << std::endl;
  ss << "Grid: x: " << mousePosGrid.x << " y: " << mousePosGrid.y << std::endl;
  ss << "Mouse clicked: ";
  if (mouseClicked) {
    ss << "Yes" << std::endl;
  } else {
    ss << "No" << std::endl;
  }
  ss << "Enemies added: " << enemiesAdded << std::endl;
  ss << "Mouse clicked: " << mouseClicked << std::endl;
  ss << "Wallet: " << wallet << std::endl;
  ss << "Game state: " << gameState << std::endl;
  ss << "Current round: " << (this->level->GetCurrentRound() + 1) << std::endl;
  if (gameState == 0) {
    ss << "Building time: " << (5 - BuildClock.getElapsedTime().asSeconds())
       << std::endl;
  }
  ss << latestMessage << std::endl;
  text.setString(ss.str());
}

// Updates tile selector that shows which tile mouse is on
void Game::updateTileSelector() {
  tileSelector.setPosition(mousePosGrid.x * gridSizeF,
                           mousePosGrid.y * gridSizeF);
}

// Main game update loop
void Game::update() {
  this->updateMousePosition();
  this->pollEvents();
  this->updateInput();
  this->updateTileSelector();
  this->updateSnowballClock();
  this->updateFireClock();
  this->updateMoveClock();
  this->updateBuildClock();
  this->updateSpawnClock();
}
/**
 * @return void
 * Clear old frame, render, display
 */
void Game::render() {
  // Clears old frame
  this->window->clear(sf::Color(0, 0, 0, 255));
  // Sets view to current view.
  this->window->setView(view);

  // Draw game elements
  // Draw every tile
  for (int x = 0; x < this->level->GetMapSize(); x++) {
    for (int y = 0; y < this->level->GetMapSize(); y++) {
      this->window->draw(this->level->tileMap[x][y]);
      if (this->level->tileMap[x][y].type_ == 2) {
        entryPointSprite.setPosition(this->level->tileMap[x][y].getPosition());
        this->window->draw(entryPointSprite);
      } else if (this->level->tileMap[x][y].type_ == 3) {
        exitPointSprite.setPosition(this->level->tileMap[x][y].getPosition());
        this->window->draw(exitPointSprite);
      } else if (this->level->tileMap[x][y].type_ == 1) {
        roadSprite.setPosition(this->level->tileMap[x][y].getPosition());
        this->window->draw(roadSprite);
      }
    }
  }
  /**
     for (int x = 0; x < this->level->GetMapSize(); x++) {
      for (int y = 0; y < this->level->GetMapSize(); y++) {
        if (this->level->tileMap[x][y].type_ = 0 &&
          this->level->tileMap[x][y].IsOccupied()) {
            for (int j = 1; j <
     (this->level->tileMap[x][y].GetTower()->GetRange() + 1); j++) { if
     ((mousePosGrid.x == this->level->tileMap[x][y].GetGridLocationX()) &&
                   (mousePosGrid.y ==
     this->level->tileMap[x][y].GetGridLocationY())) {
                rangeIndicator.setPosition(sf::Vector2f((this->level->tileMap[x][y].GetGridLocationX()
     + j) * gridSizeF, (this->level->tileMap[x][y].GetGridLocationY()) *
     gridSizeF)); this->window->draw(rangeIndicator);
                rangeIndicator.setPosition(sf::Vector2f((this->level->tileMap[x][y].GetGridLocationX()
     - j) * gridSizeF, (this->level->tileMap[x][y].GetGridLocationY()) *
     gridSizeF)); this->window->draw(rangeIndicator);
                rangeIndicator.setPosition(sf::Vector2f((this->level->tileMap[x][y].GetGridLocationX())
     * gridSizeF, (this->level->tileMap[x][y].GetGridLocationY() + j) *
     gridSizeF)); this->window->draw(rangeIndicator);
                rangeIndicator.setPosition(sf::Vector2f((this->level->tileMap[x][y].GetGridLocationX())
     * gridSizeF, (this->level->tileMap[x][y].GetGridLocationY() - j) *
     gridSizeF)); this->window->draw(rangeIndicator);
                rangeIndicator.setPosition(sf::Vector2f((this->level->tileMap[x][y].GetGridLocationX()
     + j) * gridSizeF, (this->level->tileMap[x][y].GetGridLocationY() + j) *
     gridSizeF)); this->window->draw(rangeIndicator);
                rangeIndicator.setPosition(sf::Vector2f((this->level->tileMap[x][y].GetGridLocationX()
     - j) * gridSizeF, (this->level->tileMap[x][y].GetGridLocationY() + j) *
     gridSizeF)); this->window->draw(rangeIndicator);
                rangeIndicator.setPosition(sf::Vector2f((this->level->tileMap[x][y].GetGridLocationX()
     + j) * gridSizeF, (this->level->tileMap[x][y].GetGridLocationY() - j) *
     gridSizeF)); this->window->draw(rangeIndicator);
                rangeIndicator.setPosition(sf::Vector2f((this->level->tileMap[x][y].GetGridLocationX()
     - j) * gridSizeF, (this->level->tileMap[x][y].GetGridLocationY() - j) *
     gridSizeF)); this->window->draw(rangeIndicator);
              }
            }
          }
        }
      }
      */

  for (auto i : enemies) {
    if (i->type_ == 1) {
      basicEnemySprite.setPosition(i->GetPosX() * gridSizeF,
                                   i->GetPosY() * gridSizeF);
      basicEnemySprite.move((sf::Vector2f)basicEnemyTexture.getSize() / 2.f);
      if (i->direction == 0) {
        basicEnemySprite.setRotation(0);
        basicEnemySprite.move(sf::Vector2f(2.f / 2.f, 4 * -gridSizeF / 20.f));
      } else if (i->direction == 1) {
        basicEnemySprite.setRotation(90);
      } else if (i->direction == 2) {
        basicEnemySprite.setRotation(180);
      } else if (i->direction == 3) {
        basicEnemySprite.setRotation(270);
        basicEnemySprite.move(sf::Vector2f(4 * -gridSizeF / 20.f, 1.f));
      }
      this->window->draw(basicEnemySprite);

    } else if (i->type_ == 2) {
      fastEnemySprite.setPosition(i->GetPosX() * gridSizeF,
                                  i->GetPosY() * gridSizeF);
      fastEnemySprite.move((sf::Vector2f)fastEnemyTexture.getSize() / 2.f);
      if (i->direction == 0) {
        fastEnemySprite.setRotation(0);
        fastEnemySprite.move(sf::Vector2f(2.f / 2.f, 4 * -gridSizeF / 20.f));
      } else if (i->direction == 1) {
        fastEnemySprite.setRotation(90);
      } else if (i->direction == 2) {
        fastEnemySprite.setRotation(180);
      } else if (i->direction == 3) {
        fastEnemySprite.setRotation(270);
        fastEnemySprite.move(sf::Vector2f(4 * -gridSizeF / 20.f, 1.f));
      }
      this->window->draw(fastEnemySprite);

    } else if (i->type_ == 3) {
      slowEnemySprite.setPosition(i->GetPosX() * gridSizeF,
                                  i->GetPosY() * gridSizeF);
      slowEnemySprite.move((sf::Vector2f)slowEnemyTexture.getSize() / 2.f);
      if (i->direction == 0) {
        slowEnemySprite.setRotation(0);
        slowEnemySprite.move(sf::Vector2f(2.f / 2.f, 4 * -gridSizeF / 20.f));
      } else if (i->direction == 1) {
        slowEnemySprite.setRotation(90);
      } else if (i->direction == 2) {
        slowEnemySprite.setRotation(180);
      } else if (i->direction == 3) {
        slowEnemySprite.setRotation(270);
        slowEnemySprite.move(sf::Vector2f(4 * -gridSizeF / 20.f, 1.f));
      }
      this->window->draw(slowEnemySprite);
    }
  }

  for (auto i : towers) {
    if (i->GetType() == "basic") {
      if (i->GetLevel() <= 1) {
        basicTowerSprite.setPosition(i->posX_ * gridSizeF,
                                     i->posY_ * gridSizeF);
        basicTowerSprite.move(gridSizeF / 2.f, gridSizeF / 2.f);
        auto originalRotation = basicTowerSprite.getRotation();
        if (i->hasTarget) {
          float theta =
              atan2(i->targetPosY - i->posY_, i->targetPosX - i->posX_) * 180 /
              3.141;
          theta += 90;
          basicTowerSprite.setRotation(theta);
        }
        this->window->draw(basicTowerSprite);
        basicTowerSprite.setRotation(originalRotation);

      } else if (i->GetLevel() > 1) {
        basic3TowerSprite.setPosition(i->posX_ * gridSizeF,
                                      i->posY_ * gridSizeF);
        basic3TowerSprite.move(gridSizeF / 2.f, gridSizeF / 2.f);
        auto originalRotation = basic3TowerSprite.getRotation();
        if (i->hasTarget) {
          float theta =
              atan2(i->targetPosY - i->posY_, i->targetPosX - i->posX_) * 180 /
              3.141;
          theta += 90;
          basic3TowerSprite.setRotation(theta);
        }
        this->window->draw(basic3TowerSprite);
        basic3TowerSprite.setRotation(originalRotation);
      }
    } else if (i->GetType() == "hat") {
      if (i->GetLevel() <= 1) {
        hatTowerSprite.setPosition(i->posX_ * gridSizeF, i->posY_ * gridSizeF);
        hatTowerSprite.move(gridSizeF / 2.f, gridSizeF / 2.f);
        auto originalRotation = hatTowerSprite.getRotation();
        if (i->hasTarget) {
          float theta =
              atan2(i->targetPosY - i->posY_, i->targetPosX - i->posX_) * 180 /
              3.141;
          theta += 90;
          hatTowerSprite.setRotation(theta);
        }
        this->window->draw(hatTowerSprite);
        hatTowerSprite.setRotation(originalRotation);

      } else if (i->GetLevel() > 1) {
        hat3TowerSprite.setPosition(i->posX_ * gridSizeF, i->posY_ * gridSizeF);
        hat3TowerSprite.move(gridSizeF / 2.f, gridSizeF / 2.f);
        auto originalRotation = hat3TowerSprite.getRotation();
        if (i->hasTarget) {
          float theta =
              atan2(i->targetPosY - i->posY_, i->targetPosX - i->posX_) * 180 /
              3.141;
          theta += 90;
          hat3TowerSprite.setRotation(theta);
        }
        this->window->draw(hat3TowerSprite);
        hat3TowerSprite.setRotation(originalRotation);
      }

    } else if (i->GetType() == "scarf") {
      if (i->GetLevel() <= 1) {
        scarfTowerSprite.setPosition(i->posX_ * gridSizeF,
                                     i->posY_ * gridSizeF);
        scarfTowerSprite.move(gridSizeF / 2.f, gridSizeF / 2.f);
        auto originalRotation = scarfTowerSprite.getRotation();
        if (i->hasTarget) {
          float theta =
              atan2(i->targetPosY - i->posY_, i->targetPosX - i->posX_) * 180 /
              3.141;
          theta += 90;
          scarfTowerSprite.setRotation(theta);
        }
        this->window->draw(scarfTowerSprite);
        scarfTowerSprite.setRotation(originalRotation);

      } else if (i->GetLevel() > 1) {
        scarf3TowerSprite.setPosition(i->posX_ * gridSizeF,
                                      i->posY_ * gridSizeF);
        scarf3TowerSprite.move(gridSizeF / 2.f, gridSizeF / 2.f);
        auto originalRotation = scarf3TowerSprite.getRotation();
        if (i->hasTarget) {
          float theta =
              atan2(i->targetPosY - i->posY_, i->targetPosX - i->posX_) * 180 /
              3.141;
          theta += 90;
          scarf3TowerSprite.setRotation(theta);
        }
        this->window->draw(scarf3TowerSprite);
        scarf3TowerSprite.setRotation(originalRotation);
      }
    }
  }

  for (auto i : snowballs) {
    snowballSprite.setPosition(i->GetPosX() * gridSizeF,
                               i->GetPosY() * gridSizeF);
    snowballSprite.move((sf::Vector2f)snowballTexture.getSize() / 2.f);
    this->window->draw(snowballSprite);
    // std::cout << "Snowball drawn at pos: " << i->GetPosX() << " & "
    //           << i->GetPosY() << std::endl;
  }

  // Draw the tile selector unless mouse is on top of sidebar
  if (mousePosWindow.x < 960) {
    this->window->draw(tileSelector);
  }

  // Sets view back to default view
  this->window->setView(this->window->getDefaultView());

  // Draw UI
  // Draws info text of mouse position
  // this->window->draw(text);

  // Draw sidebar
  sidebar.UpdateRoundCount(this->level->GetCurrentRound() + 1);
  sidebar.UpdateWallet(this->wallet);
  sidebar.UpdateTimer(BuildClock.getElapsedTime().asSeconds());
  sidebar.UpdateGamePhase(gameState);
  sidebar.UpdateSelection(clickSelection);
  sidebar.drawTo(*(this->window));

  // Done drawing, display to screen
  this->window->display();
}

// Private functions
// Initialization of different variables used
void Game::InitializeVariables() {
  // Window first initalized to nullptr
  this->window = nullptr;
  // Level first initalized to nullptr
  this->level = nullptr;
  // Size of tile in grid.
  this->gridSizeF = 80.f;
  // Size of tile in grid as unsigned value.
  this->gridSizeU = static_cast<unsigned>(gridSizeF);

  // Sets size for a tileselector. (You can use this as an example for how tile
  // size is set.)
  tileSelector.setSize(sf::Vector2f(gridSizeF, gridSizeF));
  // Sets color and outline for tile selector.
  tileSelector.setFillColor(sf::Color::Transparent);
  tileSelector.setOutlineThickness(1.f);
  tileSelector.setOutlineColor(sf::Color::Green);

  rangeIndicator.setSize(sf::Vector2f(gridSizeF, gridSizeF));
  rangeIndicator.setFillColor(sf::Color(255, 0, 0, 20));

  // Sets mouse position text information
  font.loadFromFile("misc/sansation.ttf");
  text.setCharacterSize(12);
  text.setFillColor(sf::Color::Green);
  text.setOutlineColor(sf::Color::Red);
  text.setFont(font);
  text.setPosition(20.f, 20.f);
  text.setString("Test");

  // Entry texture
  if (!entryPointTexture.loadFromFile("pics/rabbit_hole.png")) {
    std::cout << "Texture for entry point load failed" << std::endl;
  }
  entryPointSprite.setTexture(entryPointTexture);
  entryPointSprite.setScale(sf::Vector2f(gridSizeF / 100, gridSizeF / 100));

  // Exit texture
  if (!exitPointTexture.loadFromFile("pics/carrots.png")) {
    std::cout << "Texture for exit point load failed" << std::endl;
  }
  exitPointSprite.setTexture(exitPointTexture);
  exitPointSprite.setScale(sf::Vector2f(gridSizeF / 100, gridSizeF / 100));

  // Road texture
  if (!roadTexture.loadFromFile("pics/path.png")) {
    std::cout << "Texture for road load failed" << std::endl;
  }
  roadSprite.setTexture(roadTexture);
  roadSprite.setScale(sf::Vector2f(gridSizeF / 100, gridSizeF / 100));

  // Snowball texture
  if (!snowballTexture.loadFromFile("pics/snowball.png")) {
    std::cout << "Texture for snowball load failed" << std::endl;
  }
  snowballSprite.setTexture(snowballTexture);
  snowballSprite.setScale(sf::Vector2f(gridSizeF / 100, gridSizeF / 100));
  snowballSprite.setOrigin(((sf::Vector2f)snowballTexture.getSize() / 2.f) *
                           (gridSizeF / 100));

  // Basic enemy texture
  if (!basicEnemyTexture.loadFromFile("pics/rabbit_basic.png")) {
    std::cout << "Texture for enemy load failed" << std::endl;
  }
  basicEnemySprite.setTexture(basicEnemyTexture);
  basicEnemySprite.setScale(sf::Vector2f(gridSizeF / 100, gridSizeF / 100));
  basicEnemySprite.setOrigin(((sf::Vector2f)basicEnemyTexture.getSize() / 2.f) *
                             (gridSizeF / 100));

  // Fast enemy texture
  if (!fastEnemyTexture.loadFromFile("pics/rabbit_small.png")) {
    std::cout << "Texture for enemy load failed" << std::endl;
  }
  fastEnemySprite.setTexture(fastEnemyTexture);
  fastEnemySprite.setScale(sf::Vector2f(gridSizeF / 100, gridSizeF / 100));
  fastEnemySprite.setOrigin(((sf::Vector2f)fastEnemyTexture.getSize() / 2.f) *
                            (gridSizeF / 100));

  // Slow enemy texture
  if (!slowEnemyTexture.loadFromFile("pics/rabbit_black.png")) {
    std::cout << "Texture for enemy load failed" << std::endl;
  }
  slowEnemySprite.setTexture(slowEnemyTexture);
  slowEnemySprite.setScale(sf::Vector2f(gridSizeF / 100, gridSizeF / 100));
  slowEnemySprite.setOrigin(((sf::Vector2f)slowEnemyTexture.getSize() / 2.f) *
                            (gridSizeF / 100));

  // Basic tower texture
  if (!basicTowerTexture.loadFromFile("pics/snowman_basic1.png")) {
    std::cout << "Texture for tower load failed" << std::endl;
  }
  basicTowerSprite.setTexture(basicTowerTexture);
  basicTowerSprite.setOrigin((sf::Vector2f)basicTowerTexture.getSize() / 2.f);
  basicTowerSprite.setScale(sf::Vector2f(gridSizeF / 100, gridSizeF / 100));

  // Basic tower texture upgrade
  if (!basic3TowerTexture.loadFromFile("pics/snowman_basic3.png")) {
    std::cout << "Texture for sniper tower load failed" << std::endl;
  }
  basic3TowerSprite.setTexture(basic3TowerTexture);
  basic3TowerSprite.setOrigin((sf::Vector2f)basic3TowerTexture.getSize() / 2.f);
  basic3TowerSprite.setScale(sf::Vector2f(gridSizeF / 100, gridSizeF / 100));

  // Hat tower texture
  if (!hatTowerTexture.loadFromFile("pics/snowman_hat1.png")) {
    std::cout << "Texture for sniper tower load failed" << std::endl;
  }
  hatTowerSprite.setTexture(hatTowerTexture);
  hatTowerSprite.setOrigin((sf::Vector2f)hatTowerTexture.getSize() / 2.f);
  hatTowerSprite.setScale(sf::Vector2f(gridSizeF / 100, gridSizeF / 100));

  // Hat tower texture upgrade
  if (!hat3TowerTexture.loadFromFile("pics/snowman_hat3.png")) {
    std::cout << "Texture for sniper tower load failed" << std::endl;
  }
  hat3TowerSprite.setTexture(hat3TowerTexture);
  hat3TowerSprite.setOrigin((sf::Vector2f)hat3TowerTexture.getSize() / 2.f);
  hat3TowerSprite.setScale(sf::Vector2f(gridSizeF / 100, gridSizeF / 100));

  // Scarf tower texture
  if (!scarfTowerTexture.loadFromFile("pics/snowman_scarf1.png")) {
    std::cout << "Texture for scarf tower load failed" << std::endl;
  }
  scarfTowerSprite.setTexture(scarfTowerTexture);
  scarfTowerSprite.setOrigin((sf::Vector2f)scarfTowerTexture.getSize() / 2.f);
  scarfTowerSprite.setScale(sf::Vector2f(gridSizeF / 100, gridSizeF / 100));

  // Scarf tower texture upgrade
  if (!scarf3TowerTexture.loadFromFile("pics/snowman_scarf3.png")) {
    std::cout << "Texture for scarf tower load failed" << std::endl;
  }
  scarf3TowerSprite.setTexture(scarf3TowerTexture);
  scarf3TowerSprite.setOrigin((sf::Vector2f)scarf3TowerTexture.getSize() / 2.f);
  scarf3TowerSprite.setScale(sf::Vector2f(gridSizeF / 100, gridSizeF / 100));

  // Set the font for sidebar text
  sidebarFont.loadFromFile("misc/Sono-Regular.ttf");
  sidebar.SetFont(sidebarFont);

  // Set images in sidebar
  sidebar.GetTower1().setTexture(basicTowerTexture);
  sidebar.GetTower2().setTexture(hatTowerTexture);
  sidebar.GetTower3().setTexture(scarfTowerTexture);
}

// Initalizes window with correct size
void Game::InitializeWindow() {
  this->videoMode.height = 960;
  this->videoMode.width = 1160;
  this->window = new sf::RenderWindow(this->videoMode, "Tower Defense",
                                      sf::Style::Titlebar | sf::Style::Close);
}

// Initalizes view with same size as window
void Game::InitializeView() {
  view.setSize(1160.f, 960.f);
  view.setCenter(this->window->getSize().x / 2.f,
                 this->window->getSize().y / 2.f);
}
/**
 * @return void
 * Initializes level with default level.
 * Level can be initialized with vector of vector of strings. Each string
 * correspons to different tile type.
 *
 * 0 = Grass
 * 1 = Road
 * 2 = Entry point
 * 3 = Exit point
 *
 * Also initializes the neighbors for each tile that requires this information
 * (entry point & road). Neighbours can be initilized using vector of tuples of
 * two tuples with ints. Two tuples inside a first correspond to two tiles: Tile
 * that neighbour is going to be set and what the neighbouring tile is.
 */
void Game::InitializeLevel() {
  // Default map. You can copy this to create your own levels
  std::vector<std::vector<std::string>> defaultLevel{
      {"0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0"},
      {"0", "0", "0", "0", "1", "1", "1", "0", "0", "0", "0", "0"},
      {"0", "0", "0", "0", "1", "0", "1", "0", "0", "0", "0", "0"},
      {"2", "1", "1", "1", "1", "0", "1", "0", "0", "0", "0", "0"},
      {"0", "0", "0", "0", "0", "0", "1", "0", "0", "0", "0", "0"},
      {"0", "0", "0", "0", "0", "0", "1", "0", "0", "0", "0", "0"},
      {"0", "0", "0", "0", "0", "0", "1", "0", "0", "0", "0", "0"},
      {"0", "0", "0", "0", "0", "0", "1", "0", "0", "0", "0", "0"},
      {"0", "0", "0", "0", "0", "0", "1", "0", "0", "0", "0", "0"},
      {"0", "0", "0", "0", "0", "0", "3", "0", "0", "0", "0", "0"},
      {"0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0"},
      {"0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0"},
  };
  // Neighbour values for default map. You can copy this to create your own
  // neighbour values.:
  std::vector<std::tuple<std::tuple<int, int>, std::tuple<int, int>>>
      defaultNeighbours{
          std::make_tuple(std::make_tuple(3, 0), std::make_tuple(3, 1)),
          std::make_tuple(std::make_tuple(3, 1), std::make_tuple(3, 2)),
          std::make_tuple(std::make_tuple(3, 2), std::make_tuple(3, 3)),
          std::make_tuple(std::make_tuple(3, 3), std::make_tuple(3, 4)),
          std::make_tuple(std::make_tuple(3, 4), std::make_tuple(2, 4)),
          std::make_tuple(std::make_tuple(2, 4), std::make_tuple(1, 4)),
          std::make_tuple(std::make_tuple(1, 4), std::make_tuple(1, 5)),
          std::make_tuple(std::make_tuple(1, 5), std::make_tuple(1, 6)),
          std::make_tuple(std::make_tuple(1, 6), std::make_tuple(2, 6)),
          std::make_tuple(std::make_tuple(2, 6), std::make_tuple(3, 6)),
          std::make_tuple(std::make_tuple(3, 6), std::make_tuple(4, 6)),
          std::make_tuple(std::make_tuple(4, 6), std::make_tuple(5, 6)),
          std::make_tuple(std::make_tuple(5, 6), std::make_tuple(6, 6)),
          std::make_tuple(std::make_tuple(6, 6), std::make_tuple(7, 6)),
          std::make_tuple(std::make_tuple(7, 6), std::make_tuple(8, 6)),
          std::make_tuple(std::make_tuple(8, 6), std::make_tuple(9, 6)),
      };

  /**
   * Info for which enemy to spawn during each round.
   * Every "inner vector" corresponds to one round.
   * Enemies spawn in the order they are put into the vector.
   *
   * 1 = Basic enemy
   * 2 = Fast enemy
   * 3 = Strong enemy
   *
   * Game ends automatically when all enemies have spawned.
   */
  std::vector<std::vector<int>> defaultEnemies{
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {2, 2, 2, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 3},
      {2, 2, 2, 2, 3, 1, 1, 1, 3, 1, 3, 3, 1, 1, 3, 3, 3, 1, 1, 3, 3},
      {2, 2, 2, 2, 2, 2, 3, 3, 1, 1, 3, 3, 3,
       3, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 1, 3},
      {3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 3,
       1, 1, 1, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 3, 1},
      {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
       2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
      {2, 2, 2, 2, 2, 2, 3, 3, 1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3,
       3, 1, 1, 3, 3, 1, 3, 3, 3, 3, 1, 3, 1, 3, 1, 1, 1, 1, 3},
      {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 1, 3, 3,
       3, 3, 3, 3, 3, 1, 1, 1, 3, 1, 1, 3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 1, 3},
      {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
       3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
      {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
       2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
       3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
       3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}};

  // Calls level class constructor.
  this->level =
      new Level(12, defaultLevel, defaultNeighbours, gridSizeF, defaultEnemies);
}