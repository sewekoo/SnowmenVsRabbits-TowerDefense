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

  /**
   * @brief Checks every position in the map for enemy and then moves it to it's current direction.
   * Also transfers the enemy pointer from one tile to the next when threshold of middle point of the
   * next tile is met.
   * 
   */
  void MoveEnemies();

  /**
   * @brief Checks every position in the level for enemy and then turns it based on which direction
   * next tile from current is.
   * 
   */
  void TurnEnemies();
  /**
   * @brief Spawns next enemy from list of roundEnemies. If there's no next value then ends
   * round by returning 0.
   * 
   * @return int 
   * Returns code number of enemy type. 1 = basic, 2 = fast, 3 = strong. If no next enemy then
   * returns 0.
   */
  int SpawnNext();

  /**
   * @brief Updates roundEnemies information to next round.
   * 
   */
  void ConfigureRound();

  /**
   * @brief Increases current round variable by 1. If there's no more enemy data for next round then
   * returns true to indicate level victory.
   * 
   * @return true if last round was final, in which case level is won
   * @return false if there's still more rounds.
   */
  bool EndRound();
  /**
   * @brief Get the Current Round object
   * 
   * @return int 
   */
  int GetCurrentRound();
  /**
   * @brief Flag variable to indicate if game is lost.
   * 
   */
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