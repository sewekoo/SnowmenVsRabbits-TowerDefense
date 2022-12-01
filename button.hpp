// Class done with the help of https://www.youtube.com/watch?v=T31MoLJws4U
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream> 

class Button {
public:
    Button() { }

    Button(std::string Text, sf::Vector2f size, int charSize, sf::Color backround, sf::Color outline, sf::Color textColor) {
      text.setString(Text);
      text.setFillColor(textColor);
      button.setSize(size);
      button.setFillColor(backround);
      button.setOutlineColor(outline);
      button.setOutlineThickness(3);
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
        float posX = (pos.x + button.getLocalBounds().width / 6) -
                     (text.getLocalBounds().width / 2);
        float posY = (pos.y + button.getLocalBounds().height / 7) -
                     (text.getLocalBounds().height / 2);
        text.setPosition(posX, posY);
    }

    void drawTo(sf::RenderWindow &window) { 
        window.draw(button);
        window.draw(text);
    }

    bool MouseOnButton(sf::RenderWindow &window) {
        float MPosX = sf::Mouse::getPosition(window).x;
        float MPosY = sf::Mouse::getPosition(window).y;

        float BPosX = button.getPosition().x;
        float BPosY = button.getPosition().y;

        float BPosXWithWidth = button.getPosition().x + button.getLocalBounds().width;
        float BPosYWithHeight = button.getPosition().y + button.getLocalBounds().height;

        if (MPosX > BPosX && MPosX < BPosXWithWidth && MPosY > BPosY && MPosY < BPosYWithHeight) {
          return true;
        }
        return false;
    }

   private:
    sf::RectangleShape button;
    sf::Text text;
};