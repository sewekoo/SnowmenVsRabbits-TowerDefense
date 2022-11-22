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

// Updates game clock. May be useful with enemy movement for example
void Game::updateDt() { dt = dtClock.restart().asSeconds(); }

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
  text.setString(ss.str());
}

// Updates tile selector that shows which tile mouse is on
void Game::updateTileSelector() {
  tileSelector.setPosition(mousePosGrid.x * gridSizeF,
                           mousePosGrid.y * gridSizeF);
}

// Main game update loop
void Game::update() {
  this->updateDt();
  this->updateMousePosition();
  this->pollEvents();
  this->updateInput();
  this->updateTileSelector();
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

  // Draw entry point agains so that it's outlines go on top of its neihbours
  this->window->draw(this->level->entrypoint);

  // Draw the tile selector
  this->window->draw(tileSelector);

  // Sets view back to default view
  this->window->setView(this->window->getDefaultView());

  // Draw UI
  // Draws info text of mouse position
  this->window->draw(text);

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
  this->gridSizeF = 100.f;
  // Size of tile in grid as unsigned value.
  this->gridSizeU = static_cast<unsigned>(gridSizeF);

  // Sets size for a tileselector. (You can use this as an example for how tile
  // size is set.)
  tileSelector.setSize(sf::Vector2f(gridSizeF, gridSizeF));
  // Sets color and outline for tile selector.
  tileSelector.setFillColor(sf::Color::Transparent);
  tileSelector.setOutlineThickness(1.f);
  tileSelector.setOutlineColor(sf::Color::White);

  // Sets mouse position text information
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

// Initalizes window with correct size
void Game::InitializeWindow() {
  this->videoMode.height = 1000;
  this->videoMode.width = 1000;
  this->window = new sf::RenderWindow(this->videoMode, "Tower Defense",
                                      sf::Style::Titlebar | sf::Style::Close);
}

// Initalizes view with same size as window
void Game::InitializeView() {
  view.setSize(1000.f, 1000.f);
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
  // Calls level class constructor.
  this->level = new Level(10, defaultLevel, defaultNeighbours, gridSizeF);
}