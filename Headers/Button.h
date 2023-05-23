//
// Created by Adi on 5/16/2023.
//

#ifndef OOP_BUTTON_H
#define OOP_BUTTON_H

#include <iostream>
#include "SFML/Graphics.hpp"


class Button {
    sf::Sprite Hover;
    sf::Sprite noHover;
    sf::Sprite *curentSprite;
    sf::Vector2f position;
public:


    Button(sf::Sprite hover, sf::Sprite nohover, sf::Vector2f pos);

    Button &operator=(const Button &bt);

    Button(const Button &bt);

    Button(Button &&bt) = default;

    bool isHovered(sf::RenderWindow &gameInstance);

    bool checkClick(sf::RenderWindow &window);

    void drawButton(sf::RenderWindow &gameInstance);

    void setPos(sf::Vector2f poz);

};


#endif //OOP_BUTTON_H
