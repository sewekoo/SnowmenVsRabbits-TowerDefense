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
      int index = 0;
      getline(levelFile, line);
      value.clear();
      value.push_back(line[0]);
      one = std::stoi(value);
      value.clear();
      value.push_back(line[2]);
      two = std::stoi(value);
      value.clear();
      value.push_back(line[4]);
      three = std::stoi(value);
      value.clear();
      value.push_back(line[6]);
      four = std::stoi(value);

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
  RenderWindow MENU(VideoMode(960, 720), "MENU", Style::Default);

  RectangleShape background;
  background.setSize(Vector2f(960, 650));
  Texture Picture;
  Picture.loadFromFile("pics/menuscreen.png");
  background.setTexture(&Picture);

  Button bplay("Play", {100, 50}, 20, Color::Black, Color::White, Color::White);
  Button bexit("Exit", {100, 50}, 20, Color::Black, Color::White, Color::White);
  bplay.SetPosition({300, 500});
  bexit.SetPosition({550, 500});

  Font font;
  font.loadFromFile("misc/Sono-Regular.ttf");
  bplay.SetFont(font);
  bexit.SetFont(font);

  Text levelText;
  levelText.setString("CHOOSE YOUR LEVEL");
  levelText.setPosition({200, 100});
  levelText.setFont(font);
  levelText.setScale(2, 2);
  levelText.setFillColor(Color::White);
  levelText.setStyle(Text::Bold);

  while (MENU.isOpen()) {
    Event event;
    while (MENU.pollEvent(event)) {
      switch (event.type) {
        case Event::Closed:
          MENU.close();
        case Event::MouseMoved:
          if (bplay.MouseOnButton(MENU)) {
            bplay.SetBGColor(Color::Yellow);
          } else if (bexit.MouseOnButton(MENU)) {
            bexit.SetBGColor(Color::Yellow);
          } else if (!bplay.MouseOnButton(MENU) || !bexit.MouseOnButton(MENU)) {
            bplay.SetBGColor(Color::Black);
            bexit.SetBGColor(Color::Black);
          }
          break;
        case Event::MouseButtonPressed:
          if (bplay.MouseOnButton(MENU)) {
            RenderWindow Play(VideoMode(960, 720), "PLAY");

            Button levelA("Level 1", {140, 50}, 20, Color::Black, Color::White,
                          Color::White);
            Button levelB("Level 2", {140, 50}, 20, Color::Black, Color::White,
                          Color::White);
            Button levelC("Level 3", {140, 50}, 20, Color::Black, Color::White,
                          Color::White);

            levelA.SetPosition({170, 330});
            levelB.SetPosition({420, 330});
            levelC.SetPosition({670, 330});

            levelA.SetFont(font);
            levelB.SetFont(font);
            levelC.SetFont(font);

            MENU.close();

            while (Play.isOpen()) {
              Event p_event;
              while (Play.pollEvent(p_event)) {
                switch (p_event.type) {
                  case Event::Closed:
                    Play.close();
                  case Event::MouseMoved:
                    if (levelA.MouseOnButton(Play)) {
                      levelA.SetBGColor(Color::Yellow);
                    } else if (levelB.MouseOnButton(Play)) {
                      levelB.SetBGColor(Color::Yellow);
                    } else if (levelC.MouseOnButton(Play)) {
                      levelC.SetBGColor(Color::Yellow);
                    } else if (!levelA.MouseOnButton(Play) ||
                               !levelB.MouseOnButton(Play) ||
                               !levelC.MouseOnButton(Play)) {
                      levelA.SetBGColor(Color::Black);
                      levelB.SetBGColor(Color::Black);
                      levelC.SetBGColor(Color::Black);
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
                      break;
                    }
                }
              }
              Play.clear();
              levelA.drawTo(Play);
              levelB.drawTo(Play);
              levelC.drawTo(Play);
              Play.draw(levelText);
              Play.display();
            }
          } else if (bexit.MouseOnButton(MENU)) {
            MENU.close();
            break;
          }
      }
    }
    MENU.clear();
    MENU.draw(background);
    bplay.drawTo(MENU);
    bexit.drawTo(MENU);
    MENU.display();
  }
  return 0;
}
