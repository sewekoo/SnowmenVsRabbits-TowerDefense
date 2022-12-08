// Class done with the help of https://www.youtube.com/watch?v=T31MoLJws4U
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * @brief Class that creates a round edged button with text inside
 * 
 */

class Button {
 public:
  Button() {}

  /**
   * @brief Constructs a new Button object
   * 
   * @param Text Text inside the button
   * @param width Width of the button
   * @param height Height of the button
   * @param backround Background color for the button
   * @param outline Outline color for the button
   * @param textColor Color for the text inside button
   */
  Button(std::string Text, float width, float height, sf::Color backround,
         sf::Color outline, sf::Color textColor) {
    text.setString(Text);
    text.setFillColor(textColor);

    // Making the shape of the button
    button.setPointCount(13);
    button.setPosition({20, 20});
    button.setPoint(0, {20, 20});
    button.setPoint(1, {25, 13});
    button.setPoint(2, {30, 10});
    button.setPoint(3, {10 + width, 10});
    button.setPoint(4, {15 + width, 13});
    button.setPoint(5, {20 + width, 20});
    button.setPoint(6, {20 + width, height - 10});
    button.setPoint(7, {15 + width, height - 3});
    button.setPoint(8, {10 + width, height});
    button.setPoint(9, {30, height});
    button.setPoint(10, {25, height - 3});
    button.setPoint(11, {20, height - 10});
    button.setPoint(12, {20, 20});

    button.setFillColor(backround);
    button.setOutlineColor(outline);
    button.setOutlineThickness(5);
  }

  /**
   * @brief Set the font for the text
   * 
   * @param font 
   */
  void SetFont(sf::Font &font) { text.setFont(font); }

  /**
   * @brief Set the background color for the button
   * 
   * @param color 
   */
  void SetBGColor(sf::Color color) { button.setFillColor(color); }

  /**
   * @brief Set the text color for the text
   * 
   * @param color 
   */
  void SetTextColor(sf::Color color) { text.setFillColor(color); }

  /**
   * @brief Set the texture for the button
   * 
   * @param texture
   */
  void SetTexture(sf::Texture texture) { button.setTexture(&texture); }

  /**
   * @brief Set the button position
   * 
   * @param pos 
   */
  void SetButtonPosition(sf::Vector2f pos) { button.setPosition(pos); }

  /**
   * @brief Set the text position
   * 
   * @param pos 
   */
  void SetTextPosition(sf::Vector2f pos) { text.setPosition(pos); }

  /**
   * @brief Set the scale for the text
   * 
   * @param x Scale X
   * @param y Scale Y
   */
  void SetScale(float x, float y) { text.setScale(x, y); }

  /**
   * @brief Draw the button to the window
   * 
   * @param window Window to draw to
   */
  void drawTo(sf::RenderWindow &window) {
    window.draw(button);
    window.draw(text);
  }

  /**
   * @brief Determine whether mouse is on top of the button
   * 
   * @param window 
   * @return true 
   * @return false 
   */
  bool MouseOnButton(sf::RenderWindow &window) {
    float MPosX = sf::Mouse::getPosition(window).x;
    float MPosY = sf::Mouse::getPosition(window).y;

    float BPosX = button.getPosition().x + 20;
    float BPosY = button.getPosition().y + 8;

    float BPosXWithWidth = BPosX + button.getLocalBounds().width;
    float BPosYWithHeight = BPosY + button.getLocalBounds().height;

    if (MPosX > BPosX && MPosX < BPosXWithWidth && MPosY > BPosY &&
        MPosY < BPosYWithHeight) {
      return true;
    }
    return false;
  }

 private:
  sf::ConvexShape button;
  sf::Text text;
};