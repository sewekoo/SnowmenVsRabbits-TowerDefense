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
void Game::updateInput() {}

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