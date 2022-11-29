#include <SFML/Graphics.hpp>

#include "button.hpp"
#include "game.hpp"
using namespace sf;

int main() {
  RenderWindow MENU(VideoMode(960, 720), "MENU", Style::Default);

  Button bplay("Play", {100, 50}, 20, Color::Black, Color::White, Color::White);
  Button bexit("Exit", {100, 50}, 20, Color::Black, Color::White, Color::White);
  bplay.SetPosition({400, 200});
  bexit.SetPosition({400, 400});

  Font font;
  font.loadFromFile("Fonts/Sono-Regular.ttf");
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
                      Game game;
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
    bplay.drawTo(MENU);
    bexit.drawTo(MENU);
    MENU.display();
  }
  return 0;
}