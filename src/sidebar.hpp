#pragma once

#include <SFML/Graphics.hpp>
#include <iostream> 
#include "button.hpp"

class Sidebar {
public:
 Sidebar() { 
    /*sf::Texture basic;
    sf::Texture hat;
    sf::Texture scarf;
    if (!basic.loadFromFile("pics/snowman_basic1.png")) {
      std::cout << "not working" << std::endl;
    }
    if (!hat.loadFromFile("pics/snowman_hat1.png")) {
      std::cout << "not working" << std::endl;
    }
    if (!scarf.loadFromFile("pics/snowman_scarf1.png")) {
      std::cout << "not working" << std::endl;
    }*/
    tower1B.setFillColor(sf::Color::Blue);
    tower1B.setPosition({1010, 100});
    tower1B.setSize(sf::Vector2f(90, 90));
    tower2B.setFillColor(sf::Color::Blue);
    tower2B.setPosition({1010, 250});
    tower2B.setSize(sf::Vector2f(90, 90));
    tower3B.setFillColor(sf::Color::Blue);
    tower3B.setPosition({1010, 400});
    tower3B.setSize(sf::Vector2f(90, 90));

    goButton.setFillColor(sf::Color::Red);
    goButton.setPosition({960, 500});
    goButton.setSize(sf::Vector2f(200, 150));
    goButtonText.setString("GO");
    CenterText({960, 500});

    tower1.setPosition({1010, 100});
    tower2.setPosition({1010, 250});
    tower3.setPosition({1010, 400});

    sidebar.setSize(sf::Vector2f(200, 650));
    sidebar.setFillColor(sf::Color(255, 100, 0, 200));
    sidebar.setOutlineColor(sf::Color::Black);
    sidebar.setOutlineThickness(3);
    sidebar.setPosition(960, 0);

    roundCount.setString("Round: 1 / 5");
    roundCount.setPosition({970, 10});

    line.setSize(sf::Vector2f(200, 3));
    line.setFillColor(sf::Color::Black);
    /*line.setOutlineColor(sf::Color::Black);
    line.setOutlineThickness(3);*/
    line.setPosition(960, 50);
}

void SetFont(sf::Font &font) { 
    roundCount.setFont(font);
    goButtonText.setFont(font);
}

void UpdateRoundCount(int round) { roundCount.setString("Round: " + std::to_string(round) + " / 5"); }

void drawTo(sf::RenderWindow &window) { 
    window.draw(sidebar);
    window.draw(roundCount);
    window.draw(line);
    window.draw(tower1B);
    window.draw(tower2B);
    window.draw(tower3B);
    window.draw(tower1);
    window.draw(tower2);
    window.draw(tower3);
    window.draw(goButton);
    window.draw(goButtonText);
}

bool MouseOnButton(sf::RenderWindow &window, sf::RectangleShape button) {
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

void CenterText(sf::Vector2f posOfGoButton) { 
        float posX = (posOfGoButton.x + goButton.getLocalBounds().width / 6) -
                     (goButtonText.getLocalBounds().width / 2);
        float posY = (posOfGoButton.y + goButton.getLocalBounds().height / 7) -
                     (goButtonText.getLocalBounds().height / 2);
        goButtonText.setPosition(posX, posY);
    }

//private:
    sf::RectangleShape sidebar;
    sf::Text roundCount;
    sf::RectangleShape line;
    sf::Sprite tower1;
    sf::Sprite tower2;
    sf::Sprite tower3;
    sf::RectangleShape tower1B;
    sf::RectangleShape tower2B;
    sf::RectangleShape tower3B;
    sf::RectangleShape goButton;
    sf::Text goButtonText;
};