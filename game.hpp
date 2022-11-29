#ifndef GAME_HPP
#define GAME_HPP

#include <sstream>

#include "level.hpp"

/**
 * Class that updates the game and handles "core logic".
 */
class Game {
 public:
  // Constructors
  Game();

  /**
   * @brief Construct a new Game object with custom Level
   *
   * @param mapsize Size of one side of map
   * @param levelTiles 2D tile info with different numbers corresponding
   * different tiles
   * @param neighbourInfo Info to save what road tile or exit is next from each
   * road tile
   */
  Game(int mapsize, std::vector<std::vector<std::string>> levelTiles,
       std::vector<std::tuple<std::tuple<int, int>, std::tuple<int, int>>>
           neighbourInfo);

  // Destructors
  virtual ~Game();
  ;

  // Accessors
  const bool GetWindowIsOpen() const;

  // Functions

  /**
   * Tracks all events. For example user inputs and closing window.
   */
  void pollEvents();
  /**
   * Updates inputs.
   */
  void updateInput();
  /**
   * @brief Fires towers on the map if enemy in range
   */
  void FireTowers();
  /**
   * Updates clock.
   */
  void updateDt();

  void updateMoveClock();

  void updateFireClock();

  void spawnEnemies();

  /**
   * Updates mouse postion
   * - Relative to screen
   * - Relative to window
   * - Relative to view
   * - Relative to level grid
   */
  void updateMousePosition();
  /**
   * Updates selector that shows where mouse is moving
   */
  void updateTileSelector();
  /**
   * Update loop.
   */
  void update();
  /**
   * Renders the game.
   */
  void render();

 private:
  // Variables

  double wallet = 0;

  // Grid size
  float gridSizeF;
  unsigned gridSizeU;
  float dt = 0.f;

  // Clock
  sf::Clock dtClock;
  sf::Clock MoveClock;
  sf::Clock FireClock;
  sf::Clock SpawnClock;

  // Mouse positions
  sf::Vector2u mousePosScreen;
  sf::Vector2i mousePosWindow;
  sf::Vector2f mousePosView;
  sf::Vector2u mousePosGrid;

  // Mouse clicker flag
  bool mouseClicked = true;
  bool enemyDestroyedThisTick = false;

  // Enemies
  std::vector<Enemy*> enemies;
  int enemiesAdded = 0;

  // Towers
  std::vector<Tower*> towers;

  // Towers' hit range
  sf::RectangleShape rangeIndicator;

  // Text
  sf::Text text;
  sf::Font font;

  // Textures
  sf::Texture basicEnemyTexture;
  sf::Sprite basicEnemySprite;

  sf::Texture basicEnemyHurtTexture;
  sf::Sprite basicEnemyHurtSprite;

  sf::Texture basicTowerTexture;
  sf::Sprite basicTowerSprite;

  sf::Texture sniperTowerTexture;
  sf::Sprite sniperTowerSprite;

  sf::Texture entryPointTexture;
  sf::Sprite entryPointSprite;

  sf::Texture exitPointTexture;
  sf::Sprite exitPointSprite;

  // Level
  Level* level;

  // Window
  sf::RenderWindow* window;
  sf::VideoMode videoMode;

  // View
  sf::View view;

  // Event
  sf::Event event;

  // Selector (shows where mouse is)
  sf::RectangleShape tileSelector;

  // Initialization functions
  void InitializeVariables();
  void InitializeWindow();
  void InitializeView();
  void InitializeLevel();
};

#endif