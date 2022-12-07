#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "button.hpp"

/**
 * @brief Class that creates the sidebar
 * 
 */
class Sidebar {
 public:

 /**
  * @brief Construct a new Sidebar object
  * 
  */
  Sidebar() {

    // Create boxes around images of towers
    tower1B.setFillColor(sf::Color(0, 0, 255, 30));
    tower1B.setOutlineColor(sf::Color::White);
    tower1B.setOutlineThickness(3);
    tower1B.setPosition({1014, 100});
    tower1B.setSize(sf::Vector2f(90, 90));
    tower2B.setFillColor(sf::Color(0, 0, 255, 30));
    tower2B.setOutlineColor(sf::Color::White);
    tower2B.setOutlineThickness(3);
    tower2B.setPosition({1014, 235});
    tower2B.setSize(sf::Vector2f(90, 90));
    tower3B.setFillColor(sf::Color(0, 0, 255, 30));
    tower3B.setOutlineColor(sf::Color::White);
    tower3B.setOutlineThickness(3);
    tower3B.setPosition({1014, 370});
    tower3B.setSize(sf::Vector2f(90, 90));

    // Create box that starts the round
    goButton.setFillColor(sf::Color(255, 75, 0, 100));
    goButton.setPosition({980, 520});
    goButton.setSize(sf::Vector2f(150, 100));
    goButtonText.setString("GO");
    CenterText({960, 500});

    // Images of three different tower types
    tower1.setPosition({1010, 100});
    tower2.setPosition({1010, 235});
    tower3.setPosition({1010, 370});

    // Creating actual sidebar shape
    sidebar.setSize(sf::Vector2f(200, 650));
    sidebar.setFillColor(sf::Color(255, 255, 255, 230));
    sidebar.setOutlineColor(sf::Color(0, 0, 0, 30));
    sidebar.setOutlineThickness(3);
    sidebar.setPosition(960, 0);

    // Round counter
    roundCount.setString("Round: 1 / 5");
    roundCount.setPosition({970, 5});

    // Wallet situation
    wallet.setString("Wallet: ");
    wallet.setPosition({970, 50});

    // Setting the information of both the regular and update prices of all towers
    basicPrice.setString("Price: x$");
    basicPrice.setPosition({1025, 195});
    basicPrice.setCharacterSize(12);
    basicPrice.setFillColor(sf::Color::Black);

    basicUpgrade.setString("Upgrade: x$");
    basicUpgrade.setPosition({1020, 212});
    basicUpgrade.setCharacterSize(12);
    basicUpgrade.setFillColor(sf::Color::Black);

    hatPrice.setString("Price: x$");
    hatPrice.setPosition({1025, 330});
    hatPrice.setCharacterSize(12);
    hatPrice.setFillColor(sf::Color::Black);

    hatUpgrade.setString("Upgrade: x$");
    hatUpgrade.setPosition({1020, 347});
    hatUpgrade.setCharacterSize(12);
    hatUpgrade.setFillColor(sf::Color::Black);

    scarfPrice.setString("Price: x$");
    scarfPrice.setPosition({1025, 465});
    scarfPrice.setCharacterSize(12);
    scarfPrice.setFillColor(sf::Color::Black);

    scarfUpgrade.setString("Upgrade: x$");
    scarfUpgrade.setPosition({1020, 482});
    scarfUpgrade.setCharacterSize(12);
    scarfUpgrade.setFillColor(sf::Color::Black);

    // Lines to draw that separate the roundcounter and wallet
    line1.setSize(sf::Vector2f(200, 3));
    line1.setFillColor(sf::Color(0, 0, 0, 30));
    line1.setPosition(960, 45);

    line2.setSize(sf::Vector2f(200, 3));
    line2.setFillColor(sf::Color(0, 0, 0, 30));
    line2.setPosition(960, 90);
  }

  /**
   * @brief Set the font for all text in sidebar
   * 
   * @param font 
   */
  void SetFont(sf::Font &font) {
    roundCount.setFont(font);
    wallet.setFont(font);
    goButtonText.setFont(font);
    basicPrice.setFont(font);
    basicUpgrade.setFont(font);
    hatPrice.setFont(font);
    hatUpgrade.setFont(font);
    scarfPrice.setFont(font);
    scarfUpgrade.setFont(font);
  }

  /**
   * @brief Round count updater
   * 
   * @param round 
   */
  void UpdateRoundCount(int round) {
    roundCount.setString("Round: " + std::to_string(round) + " / 5");
  }

  /**
   * @brief Updating wallet counter
   * 
   * @param amount 
   */
  void UpdateWallet(int amount) {
    wallet.setString("Wallet: " + std::to_string(amount) + "$");
  }

  /**
   * @brief Drawing all the elements of the sidebar
   * 
   * @param window Window to draw to
   */
  void drawTo(sf::RenderWindow &window) {
    window.draw(sidebar);
    window.draw(roundCount);
    window.draw(wallet);
    window.draw(line1);
    window.draw(line2);
    window.draw(basicPrice);
    window.draw(basicUpgrade);
    window.draw(hatPrice);
    window.draw(hatUpgrade);
    window.draw(scarfPrice);
    window.draw(scarfUpgrade);
    window.draw(tower1B);
    window.draw(tower2B);
    window.draw(tower3B);
    window.draw(tower1);
    window.draw(tower2);
    window.draw(tower3);
    window.draw(goButton);
    window.draw(goButtonText);
  }

  /**
   * @brief Function to determine if mouse is on top of the shape
   * 
   * @param window
   * @param button Rectangle that mouse is on top of
   * @return true 
   * @return false 
   */
  bool MouseOnButton(sf::RenderWindow &window, sf::RectangleShape button) {
    float MPosX = sf::Mouse::getPosition(window).x;
    float MPosY = sf::Mouse::getPosition(window).y;

    float BPosX = button.getPosition().x;
    float BPosY = button.getPosition().y;

    float BPosXWithWidth =
        button.getPosition().x + button.getLocalBounds().width;
    float BPosYWithHeight =
        button.getPosition().y + button.getLocalBounds().height;

    if (MPosX > BPosX && MPosX < BPosXWithWidth && MPosY > BPosY &&
        MPosY < BPosYWithHeight) {
      return true;
    }
    return false;
  }

  /**
   * @brief Centering text on top of the shape
   * 
   * @param posOfGoButton Position of the shape the text should be in the center of
   */
  void CenterText(sf::Vector2f posOfGoButton) {
    float posX = (posOfGoButton.x + goButton.getLocalBounds().width / 2) -
                 (goButtonText.getLocalBounds().width / 2);
    float posY = (posOfGoButton.y + goButton.getLocalBounds().height / 2) -
                 (goButtonText.getLocalBounds().height / 2);
    goButtonText.setPosition(posX, posY);
  }

  // Getter functions

  sf::Sprite& GetTower1() { return tower1; }
  sf::Sprite& GetTower2() { return tower2; }
  sf::Sprite& GetTower3() { return tower3; }

  const sf::RectangleShape& GetTower1B() const { return tower1B; }
  const sf::RectangleShape& GetTower2B() const { return tower2B; }
  const sf::RectangleShape& GetTower3B() const { return tower3B; }

  const sf::RectangleShape& GetGoButton() const { return goButton; }

 private:
  sf::RectangleShape sidebar;
  sf::Text roundCount;
  sf::Text wallet;
  sf::Text basicPrice;
  sf::Text basicUpgrade;
  sf::Text hatPrice;
  sf::Text hatUpgrade;
  sf::Text scarfPrice;
  sf::Text scarfUpgrade;
  sf::RectangleShape line1;
  sf::RectangleShape line2;
  sf::Sprite tower1;
  sf::Sprite tower2;
  sf::Sprite tower3;
  sf::RectangleShape tower1B;
  sf::RectangleShape tower2B;
  sf::RectangleShape tower3B;
  sf::RectangleShape goButton;
  sf::Text goButtonText;
};