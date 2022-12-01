#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <tuple>
#include <vector>

#include "entrypoint.hpp"
#include "exitpoint.hpp"
#include "grass.hpp"
#include "road.hpp"

class Level {
 public:
  // Constructors
  Level(const int mapSize, std::vector<std::vector<std::string>> levelInfo,
        float gridSizeF);

  Level(const int mapSize, std::vector<std::vector<std::string>> levelInfo,
        std::vector<std::tuple<std::tuple<int, int>, std::tuple<int, int>>>
            neighbourInfo,
        float gridSizeF);

  Level(const int mapSize, std::vector<std::vector<std::string>> levelInfo,
        std::vector<std::tuple<std::tuple<int, int>, std::tuple<int, int>>>
            neighbourInfo,
        float gridSizeF, std::vector<std::vector<int>> enemyInfo);

  // Destructor
  ~Level();

  // Values for drawing the level:
  std::vector<std::vector<Tile>> tileMap;
  EntryPoint entrypoint;
  ExitPoint exitpoint;
  std::vector<Road> roads;

  /**
   * Initalizes level
   */
  void initializeLevel();

  /**
   * Initalizes neighbour values
   */
  void initalizeNeighbours();

  /**
   * @return Map size as int
   */
  int GetMapSize();

  void MoveEnemies();

  void TurnEnemies();

  int SpawnNext();

  void ConfigureRound();

  bool EndRound();

  int GetCurrentRound();

  bool LevelLost = false;

 private:
  const int mapSize_;
  std::vector<std::vector<std::string>> levelInfo_;
  std::vector<std::tuple<std::tuple<int, int>, std::tuple<int, int>>>
      neighbourInfo_;
  float gridSizeF_;
  std::vector<std::vector<int>> enemyInfo_;
  std::vector<int> roundEnemies;
  int currentRound;
};

#endif