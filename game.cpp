#include "game.hpp"

// Constructors
Game::Game() {
  this->InitializeVariables();
  this->InitializeWindow();
  this->InitializeLevel();
}

// Destructors
Game::~Game() {
  delete this->window;
  delete this->level;
  for (auto i : towers) {
    delete i;
  }
}

// Functions

const bool Game::GetWindowIsOpen() const { return this->window->isOpen(); }

void Game::pollEvents() {
  while (this->window->pollEvent(event)) {
    switch (this->event.type) {
      // Closes the window when closed
      case sf::Event::Closed:
        this->window->close();
        break;
      // Closes the window with escape button
      case sf::Event::KeyPressed:
        if (this->event.key.code == sf::Keyboard::Escape) {
          this->window->close();
        }
        break;
    }
  }
}

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
          std::cout << "Tower upgrade sequence began" << std::endl;
          if (this->level->tileMap[x][y].GetTower() != nullptr) {
            std::cout << "Tile tower value is not nullptr. Trying to upgrade:"
                      << std::endl;
            try {
              std::cout << this->level->tileMap[x][y].occupantTower_
                        << "level: "
                        << this->level->tileMap[x][y].occupantTower_->GetLevel()
                        << std::endl;
              this->level->tileMap[x][y].occupantTower_->Upgrade();
              std::cout << "Upgrade success. New level: "
                        << this->level->tileMap[x][y].occupantTower_->GetLevel()
                        << std::endl;
            } catch (const std::exception& e) {
              std::cout << "Upgrade failed" << std::endl;
            }
          }
        }

        if ((this->level->tileMap[x][y].IsOccupied()) &&
            (this->level->tileMap[x][y].type_ == 1) &&
            (this->level->tileMap[x][y].GetGridLocationX() == mousePosGrid.x) &&
            (this->level->tileMap[x][y].GetGridLocationY() == mousePosGrid.y)) {
          if (this->level->tileMap[x][y].GetEnemy()->TakeDamage(10)) {
            std::cout << "Enemy is killed (but not deleted)" << std::endl;
          }
          std::cout << "Enemy hp: "
                    << this->level->tileMap[x][y].GetEnemy()->GetHP()
                    << std::endl;
        }

        if ((!this->level->tileMap[x][y].IsOccupied()) &&
            (this->level->tileMap[x][y].type_ == 1) &&
            (this->level->tileMap[x][y].GetGridLocationX() == mousePosGrid.x) &&
            (this->level->tileMap[x][y].GetGridLocationY() == mousePosGrid.y)) {
          std::cout << "MousePos X & Y: " << mousePosGrid.x << " "
                    << mousePosGrid.y << std::endl;
          std::cout << "TilePos X & Y: "
                    << this->level->tileMap[x][y].GetGridLocationX() << " "
                    << this->level->tileMap[x][y].GetGridLocationY()
                    << std::endl;
          std::cout << "Enemy adding sequence began" << std::endl;
          Enemy* newEnemy =
              new EasyEnemy(this->mousePosGrid.x, this->mousePosGrid.y);
          std::cout << "Enemy created into variable succesful" << std::endl;
          enemies.push_back(newEnemy);
          std::cout << "Enemy pushed to enemies vector succesful" << std::endl;
          this->level->tileMap[x][y].addOccupant(newEnemy);
          enemiesAdded++;
          this->level->tileMap[x][y].MakeOccupied();
          std::cout << "Succesfully increased enemy counter" << std::endl;
        }
        if ((!this->level->tileMap[x][y].IsOccupied()) &&
            (this->level->tileMap[x][y].type_ == 0) &&
            (this->level->tileMap[x][y].GetGridLocationX() == mousePosGrid.x) &&
            (this->level->tileMap[x][y].GetGridLocationY() == mousePosGrid.y)) {
          Tower* newTower =
              new Tower(this->mousePosGrid.x, this->mousePosGrid.y);
          towers.push_back(newTower);
          this->level->tileMap[x][y].addOccupant(newTower);
          this->level->tileMap[x][y].MakeOccupied();
        }
      }
    }
  }
}

void Game::updateDt() { dt = dtClock.restart().asSeconds(); }

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
  text.setString(ss.str());
}

void Game::updateTileSelector() {
  tileSelector.setPosition(mousePosGrid.x * gridSizeF,
                           mousePosGrid.y * gridSizeF);
}

void Game::update() {
  this->updateDt();
  this->updateInput();
  this->updateMousePosition();
  this->pollEvents();
  this->updateTileSelector();
}
/**
 * @return void
 * Clear old frame, render, display
 */
void Game::render() {
  this->window->clear(sf::Color(0, 0, 0, 255));
  this->window->setView(view);

  // Draw game elements

  this->window->setView(this->window->getDefaultView());

  for (int x = 0; x < this->level->GetMapSize(); x++) {
    for (int y = 0; y < this->level->GetMapSize(); y++) {
      this->window->draw(this->level->tileMap[x][y]);
    }
  }

  for (auto i : enemies) {
    basicEnemySprite.setPosition(i->GetPosX() * gridSizeF,
                                 i->GetPosY() * gridSizeF);
    if (i->GetHP() >= 1) {
      this->window->draw(basicEnemySprite);
    } else {
      // basicEnemyHurtSprite.setPosition(i->GetPosX() * gridSizeF,
      //                                  i->GetPosY() * gridSizeF);
      // this->window->draw(basicEnemyHurtSprite);
      sf::Color original = basicEnemySprite.getColor();
      basicEnemySprite.setColor(sf::Color::Red);
      this->window->draw(basicEnemySprite);
      basicEnemySprite.setColor(original);
    }
  }

  for (auto i : towers) {
    if (i->GetLevel() <= 1) {
      basicTowerSprite.setPosition(i->posX_ * gridSizeF, i->posY_ * gridSizeF);
      this->window->draw(basicTowerSprite);
    } else {
      sniperTowerSprite.setPosition(i->posX_ * gridSizeF, i->posY_ * gridSizeF);
      this->window->draw(sniperTowerSprite);
    }
  }

  this->window->draw(this->level->entrypoint);
  this->window->draw(tileSelector);

  // Draw UI
  this->window->draw(text);

  // Done drawing, display to screen
  this->window->display();
}

// Private functions
void Game::InitializeVariables() {
  this->window = nullptr;
  this->level = nullptr;
  this->gridSizeF = 100.f;
  this->gridSizeU = static_cast<unsigned>(gridSizeF);

  tileSelector.setSize(sf::Vector2f(gridSizeF, gridSizeF));
  tileSelector.setFillColor(sf::Color::Transparent);
  tileSelector.setOutlineThickness(1.f);
  tileSelector.setOutlineColor(sf::Color::White);

  font.loadFromFile("Fonts/sansation.ttf");
  text.setCharacterSize(12);
  text.setFillColor(sf::Color::White);
  text.setOutlineColor(sf::Color::Red);
  text.setFont(font);
  text.setPosition(20.f, 20.f);
  text.setString("Test");

  if (!basicEnemyTexture.loadFromFile("pics/rabbit_basic_crop.png")) {
    std::cout << "Texture for enemy load failed" << std::endl;
  }
  basicEnemySprite.setTexture(basicEnemyTexture);

  if (!basicEnemyHurtTexture.loadFromFile("pics/rabbit_basic_crop.png")) {
    std::cout << "Texture for enemy load failed" << std::endl;
  }
  basicEnemyHurtSprite.setTexture(basicEnemyHurtTexture);
  basicEnemyHurtSprite.setColor(sf::Color::Red);

  if (!basicTowerTexture.loadFromFile("pics/snowman_basic_crop.png")) {
    std::cout << "Texture for tower load failed" << std::endl;
  }
  basicTowerSprite.setTexture(basicTowerTexture);

  if (!sniperTowerTexture.loadFromFile("pics/snowman_hat_crop.png")) {
    std::cout << "Texture for sniper tower load failed" << std::endl;
  }
  sniperTowerSprite.setTexture(sniperTowerTexture);
}

void Game::InitializeWindow() {
  this->videoMode.height = 1000;
  this->videoMode.width = 1000;
  this->window = new sf::RenderWindow(this->videoMode, "Tower Defense",
                                      sf::Style::Titlebar | sf::Style::Close);
}

void Game::InitializeView() {
  view.setSize(1000.f, 1000.f);
  view.setCenter(this->window->getSize().x / 2.f,
                 this->window->getSize().y / 2.f);
}

void Game::InitializeLevel() {
  // Default map:
  std::vector<std::vector<std::string>> defaultLevel{
      {"0", "0", "0", "0", "0", "0", "0", "0", "0", "0"},
      {"0", "0", "0", "0", "1", "1", "1", "0", "0", "0"},
      {"0", "0", "0", "0", "1", "0", "1", "0", "0", "0"},
      {"2", "1", "1", "1", "1", "0", "1", "0", "0", "0"},
      {"0", "0", "0", "0", "0", "0", "1", "0", "0", "0"},
      {"0", "0", "0", "0", "0", "0", "1", "0", "0", "0"},
      {"0", "0", "0", "0", "0", "0", "1", "0", "0", "0"},
      {"0", "0", "0", "0", "0", "0", "1", "0", "0", "0"},
      {"0", "0", "0", "0", "0", "0", "1", "0", "0", "0"},
      {"0", "0", "0", "0", "0", "0", "3", "0", "0", "0"},
  };
  // Neighbour values for default map:
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
  this->level = new Level(10, defaultLevel, defaultNeighbours, gridSizeF);
}