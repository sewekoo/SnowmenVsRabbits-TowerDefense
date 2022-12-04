// Class done with the help of https://www.youtube.com/watch?v=T31MoLJws4U
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream> 

class Button {
public:
    Button() { }

    Button(std::string Text, float width, float height, sf::Color backround, sf::Color outline, sf::Color textColor) {
      text.setString(Text);
      text.setFillColor(textColor);

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

    void SetFont(sf::Font &font) { text.setFont(font); }

    void SetBGColor(sf::Color color) {
        button.setFillColor(color);
    }

    void SetTextColor(sf::Color color) {
        text.setFillColor(color);
    }

    void SetTexture(sf::Texture texture) { 
        button.setTexture(&texture); 
    }

    void SetPosition(sf::Vector2f pos) { 
        button.setPosition(pos);
        float posX = (pos.x + button.getLocalBounds().width / 2.5) -
                     (text.getLocalBounds().width / 2);
        float posY = (pos.y + button.getLocalBounds().height / 3) -
                     (text.getLocalBounds().height / 2);
        text.setPosition(posX, posY);
    }

    sf::Text getText() { return text; }

    void drawTo(sf::RenderWindow &window) { 
        window.draw(button);
        window.draw(text);
    }

    bool MouseOnButton(sf::RenderWindow &window) {
        float MPosX = sf::Mouse::getPosition(window).x;
        float MPosY = sf::Mouse::getPosition(window).y;

        float BPosX = button.getPosition().x + 20;
        float BPosY = button.getPosition().y + 8;

        float BPosXWithWidth = BPosX + button.getLocalBounds().width;
        float BPosYWithHeight = BPosY + button.getLocalBounds().height;

        if (MPosX > BPosX && MPosX < BPosXWithWidth && MPosY > BPosY && MPosY < BPosYWithHeight) {
          return true;
        }
        return false;
    }

   private:
    sf::ConvexShape button;
    sf::Text text;
};