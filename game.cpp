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

const bool Game::GetWindowIsOpen() const { return this->window->isOpen(); }

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

void Game::updateInput() {}

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
  text.setString(ss.str());
}

void Game::updateTileSelector() {
  tileSelector.setPosition(mousePosGrid.x * gridSizeF,
                           mousePosGrid.y * gridSizeF);
}

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
  this->window->clear(sf::Color(0, 0, 0, 255));
  this->window->setView(view);

  // Draw game elements

  this->window->setView(this->window->getDefaultView());

  for (int x = 0; x < this->level->GetMapSize(); x++) {
    for (int y = 0; y < this->level->GetMapSize(); y++) {
      this->window->draw(this->level->tileMap[x][y]);
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