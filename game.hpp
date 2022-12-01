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

  Game(int mapsize, std::vector<std::vector<std::string>> levelTiles,
       std::vector<std::tuple<std::tuple<int, int>, std::tuple<int, int>>>
           neighbourInfo,
       std::vector<std::vector<int>> enemyInfo);

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
   * @brief Updates spawn timer.
   */
  void updateSpawnClock();
  /**
   * @brief Updates building phase timer.
   */
  void updateBuildClock();
  /**
   * Updates clock.
   */
  void updateDt();
  /**
   * @brief Updates enemy move timer.
   *
   */
  void updateMoveClock();
  /**
   * @brief Updates tower firing timer.
   *
   */
  void updateFireClock();
  /**
   * Spawns enemies
   */
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

  // 0 => building phase, 1 => active wave, 2 => level won
  int gameState = 0;

  double wallet = 100;

  std::string latestMessage = "";

  // Grid size
  float gridSizeF;
  unsigned gridSizeU;
  float dt = 0.f;
  // Clock
  sf::Clock dtClock;
  sf::Clock MoveClock;
  sf::Clock FireClock;
  sf::Clock SpawnClock;
  sf::Clock BuildClock;

  // Mouse positions
  sf::Vector2u mousePosScreen;
  sf::Vector2i mousePosWindow;
  sf::Vector2f mousePosView;
  sf::Vector2u mousePosGrid;

  // Mouse clicker flag
  bool mouseClicked = true;

  // Enemy detroyer flag (so it doesnt create a new one straight away)
  bool enemyDestroyedThisTick = false;

  // Enemies
  std::vector<Enemy*> enemies;
  int enemiesAdded = 0;

  // Towers
  std::vector<Tower*> towers;

  // Towers' hit range
  sf::RectangleShape rangeIndicator;

  // Textures
  sf::Texture roadTexture;
  sf::Sprite roadSprite;

  sf::Texture basicEnemyTexture;
  sf::Sprite basicEnemySprite;

  sf::Texture fastEnemyTexture;
  sf::Sprite fastEnemySprite;

  sf::Texture slowEnemyTexture;
  sf::Sprite slowEnemySprite;

  sf::Texture basicTowerTexture;
  sf::Sprite basicTowerSprite;

  sf::Texture sniperTowerTexture;
  sf::Sprite sniperTowerSprite;

  sf::Texture entryPointTexture;
  sf::Sprite entryPointSprite;

  sf::Texture exitPointTexture;
  sf::Sprite exitPointSprite;

  // Text
  sf::Text text;
  sf::Font font;

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
   * (entry point & road). Neighbours can be initilized using vector of tuples
   * of two tuples with ints. Two tuples inside a first correspond to two tiles:
   * Tile that neighbour is going to be set and what the neighbouring tile is.
   */
  void InitializeLevel();
};

#endif