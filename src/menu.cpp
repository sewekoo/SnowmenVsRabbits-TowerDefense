#include <SFML/Graphics.hpp>
#include <fstream>

#include "button.hpp"
#include "game.hpp"
using namespace sf;

std::vector<std::vector<int>> defaultEnemies{
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 2},
    {1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 3}, {2, 1, 3, 1, 2, 3, 1, 1, 3, 1, 2, 2},
    {2, 2, 3, 2, 2, 3, 3, 3, 2, 2, 2, 3},
};

std::vector<std::tuple<std::tuple<int, int>, std::tuple<int, int>>>
    defaultNeighbours2;

std::vector<std::vector<std::string>> defaultLevel2;

void loadLevel(std::string levelName) {
  std::ifstream levelFile(levelName);

  std::string line;
  std::string value;
  std::tuple<std::tuple<int, int>, std::tuple<int, int>> oneTuple;
  int one, two, three, four;

  if (!levelFile.is_open()) {
    perror("Can't open file");
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
        defaultNeighbours3{
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
  } else {
    // Read the grid values in from the file
    for (auto i = 0; i < 12; i++) {
      getline(levelFile, line);
      std::vector<std::string> oneVector;
      for (int j = 0; j < 24; j++) {
        value = line[j];
        if (line[j] != ',') {
          oneVector.push_back(value);
        }
      }
      defaultLevel2.push_back(oneVector);
    }

    // Read the neighbor values in from the file
    while (levelFile.good()) {
      getline(levelFile, line);
      int var = 1;
      value.clear();
      for (auto ii = 0; ii < line.size(); ii++) {
        if (line[ii] != ',') {
          value.push_back(line[ii]);
        } else {
          if (var == 1) {
            one = std::stoi(value);
            value.clear();
          } else if (var == 2) {
            two = std::stoi(value);
            value.clear();
          } else if (var == 3) {
            three = std::stoi(value);
            value.clear();
          } else if (var == 4) {
            four = std::stoi(value);
            value.clear();
          } else {
            // do nothing
          }
          var++;
        }
      }
      oneTuple = std::make_tuple(std::make_tuple(one, two),
                                 std::make_tuple(three, four));
      defaultNeighbours2.push_back(oneTuple);
    }
  }

  std::vector<std::vector<int>> defaultEnemies{
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1},
      {0, 2, 0, 2, 0, 2, 0, 0, 2, 0, 2, 2},
      {1, 0, 2, 0, 1, 2, 0, 0, 2, 0, 1, 1},
      {1, 1, 2, 1, 1, 2, 2, 2, 1, 1, 1, 2},
  };
}

int main() {
  // Window for the menu
  RenderWindow MENU(VideoMode(960, 720), "MENU", Style::Default);

  // Backgrounds for both the menu and level choosing window
  RectangleShape menuBackground;
  menuBackground.setSize(Vector2f(960, 650));
  Texture Picture;
  Picture.loadFromFile("pics/menuscreen.png");
  menuBackground.setTexture(&Picture);

  RectangleShape levelbackground;
  levelbackground.setSize(Vector2f(960, 650));
  Texture PictureLevel;
  PictureLevel.loadFromFile("pics/carrotbackground.png");
  levelbackground.setTexture(&PictureLevel);

  // Creating buttons for MENU (bplay = button for play, bexit = button for exit)
  Button bplay("PLAY", 200, 100, Color(0, 0, 0, 10), Color(0, 0, 130, 50),
               Color(0, 0, 130, 50));
  Button bexit("EXIT", 200, 100, Color(0, 0, 0, 10), Color(0, 0, 130, 50),
               Color(0, 0, 130, 50));
  bplay.SetButtonPosition({200, 500});
  bexit.SetButtonPosition({450, 500});
  bplay.SetTextPosition({285, 530});
  bexit.SetTextPosition({535, 530});

  // The font for both menu and level choosing window
  Font font;
  font.loadFromFile("misc/Sono-Regular.ttf");
  bplay.SetFont(font);
  bexit.SetFont(font);

  // Text for the level choosing window
  Text levelText;
  levelText.setString("CHOOSE A LEVEL");
  levelText.setPosition({205, 150});
  levelText.setFont(font);
  levelText.setScale(2, 2);
  levelText.setFillColor(Color(0, 0, 0, 255));
  levelText.setStyle(Text::Bold);
  RectangleShape levelTextBG;
  levelTextBG.setFillColor(Color(255, 255, 255, 230));
  levelTextBG.setSize({500, 100});
  levelTextBG.setPosition({200, 145});

  // Running MENU window. When mouse is on top of a button, it changes color. Pressing on Exit button closes the window
  // and pressing on Play opens the level choosing window
  while (MENU.isOpen()) {
    Event event;
    while (MENU.pollEvent(event)) {
      switch (event.type) {
        case Event::Closed:
          MENU.close();
        case Event::MouseMoved:
          if (bplay.MouseOnButton(MENU)) {
            bplay.SetBGColor(Color(0, 0, 255, 30));
          } else if (bexit.MouseOnButton(MENU)) {
            bexit.SetBGColor(Color(0, 0, 255, 30));
          } else if (!bplay.MouseOnButton(MENU) || !bexit.MouseOnButton(MENU)) {
            bplay.SetBGColor(Color(0, 0, 0, 10));
            bexit.SetBGColor(Color(0, 0, 0, 10));
          }
          break;
        case Event::MouseButtonPressed:
        // Running Play window. When mouse is on top of a button, it changes color. Pressing on different level numbers opens varying
        // levels and creates a new Game class. The level is read from a file according to the code written in the beginning of this file
          if (bplay.MouseOnButton(MENU)) {
            // Window for level choosing
            RenderWindow Play(VideoMode(960, 720), "PLAY");

            Button levelA("1", 140, 140, Color(0, 0, 0, 10),
                          Color(0, 0, 0, 255), Color(0, 0, 0, 255));
            Button levelB("2", 140, 140, Color(0, 0, 0, 10),
                          Color(0, 0, 0, 255), Color(0, 0, 0, 255));
            Button levelC("3", 140, 140, Color(0, 0, 0, 10),
                          Color(0, 0, 0, 255), Color(0, 0, 0, 255));
            Button levelD("4", 140, 140, Color(0, 0, 0, 10),
                          Color(0, 0, 0, 255), Color(0, 0, 0, 255));
            Button levelE("5", 140, 140, Color(0, 0, 0, 10),
                          Color(0, 0, 0, 255), Color(0, 0, 0, 255));
            levelA.SetScale(2, 2);
            levelB.SetScale(2, 2);
            levelC.SetScale(2, 2);
            levelD.SetScale(2, 2);
            levelE.SetScale(2, 2);

            levelA.SetButtonPosition({25, 330});
            levelB.SetButtonPosition({200, 330});
            levelC.SetButtonPosition({375, 330});
            levelD.SetButtonPosition({550, 330});
            levelE.SetButtonPosition({725, 330});

            levelA.SetTextPosition({100, 365});
            levelB.SetTextPosition({275, 365});
            levelC.SetTextPosition({450, 365});
            levelD.SetTextPosition({625, 365});
            levelE.SetTextPosition({800, 365});

            levelA.SetFont(font);
            levelB.SetFont(font);
            levelC.SetFont(font);
            levelD.SetFont(font);
            levelE.SetFont(font);

            while (Play.isOpen()) {
              Event p_event;
              while (Play.pollEvent(p_event)) {
                switch (p_event.type) {
                  case Event::Closed:
                    Play.close();
                  case Event::MouseMoved:
                    if (levelA.MouseOnButton(Play)) {
                      levelA.SetBGColor(Color(0, 0, 255, 30));
                    } else if (levelB.MouseOnButton(Play)) {
                      levelB.SetBGColor(Color(0, 0, 255, 30));
                    } else if (levelC.MouseOnButton(Play)) {
                      levelC.SetBGColor(Color(0, 0, 255, 30));
                    } else if (levelD.MouseOnButton(Play)) {
                      levelD.SetBGColor(Color(0, 0, 255, 30));
                    } else if (levelE.MouseOnButton(Play)) {
                      levelE.SetBGColor(Color(0, 0, 255, 30));
                    } else if (!levelA.MouseOnButton(Play) ||
                               !levelB.MouseOnButton(Play) ||
                               !levelC.MouseOnButton(Play) ||
                               !levelD.MouseOnButton(Play) ||
                               !levelE.MouseOnButton(Play)) {
                      levelA.SetBGColor(Color(0, 0, 0, 10));
                      levelB.SetBGColor(Color(0, 0, 0, 10));
                      levelC.SetBGColor(Color(0, 0, 0, 10));
                      levelD.SetBGColor(Color(0, 0, 0, 10));
                      levelE.SetBGColor(Color(0, 0, 0, 10));
                    }
                    break;
                  case Event::MouseButtonPressed:
                    if (levelA.MouseOnButton(Play)) {
                      int size = 12;
                      loadLevel("src/level.txt");
                      Game game{size, defaultLevel2, defaultNeighbours2,
                                defaultEnemies};
                      while (game.GetWindowIsOpen()) {
                        game.update();
                        game.render();
                      }
                      // break;
                    } else if (levelB.MouseOnButton(Play)) {
                      int size = 12;
                      loadLevel("src/level2.txt");
                      Game game{size, defaultLevel2, defaultNeighbours2,
                                defaultEnemies};
                      while (game.GetWindowIsOpen()) {
                        game.update();
                        game.render();
                      }
                      // break;
                    } else if (levelC.MouseOnButton(Play)) {
                      int size = 12;
                      loadLevel("src/level3.txt");
                      Game game{size, defaultLevel2, defaultNeighbours2,
                                defaultEnemies};
                      while (game.GetWindowIsOpen()) {
                        game.update();
                        game.render();
                      }
                      // break;
                    } else if (levelD.MouseOnButton(Play)) {
                      int size = 12;
                      loadLevel("src/level4.txt");
                      Game game{size, defaultLevel2, defaultNeighbours2,
                                defaultEnemies};
                      while (game.GetWindowIsOpen()) {
                        game.update();
                        game.render();
                      }
                      // break;
                    } else if (levelE.MouseOnButton(Play)) {
                      int size = 12;
                      loadLevel("src/level5.txt");
                      Game game{size, defaultLevel2, defaultNeighbours2,
                                defaultEnemies};
                      while (game.GetWindowIsOpen()) {
                        game.update();
                        game.render();
                      }
                      // break;
                    }
                }
                break;
              }
              // Drawing all the Play window elements
              Play.clear();
              Play.draw(levelbackground);
              levelA.drawTo(Play);
              levelB.drawTo(Play);
              levelC.drawTo(Play);
              levelD.drawTo(Play);
              levelE.drawTo(Play);
              Play.draw(levelTextBG);
              Play.draw(levelText);
              Play.display();
            }
          } else if (bexit.MouseOnButton(MENU)) {
            MENU.close();
            break;
          }
      }
    }
    // Drawing all the MENU window elements
    MENU.clear();
    MENU.draw(menuBackground);
    bplay.drawTo(MENU);
    bexit.drawTo(MENU);
    MENU.display();
  }
  return 0;
}
