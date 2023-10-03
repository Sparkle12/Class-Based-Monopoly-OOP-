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

    /// Takes the display window as a paramter and checks if the button is hovered returning true/false
    bool isHovered(sf::RenderWindow &gameInstance);

    /// Takes the display window as a parameter and checks if the button is clicked returning true/false
    bool checkClick(sf::RenderWindow &window);

    /// Takes the display window as a parameter and draws the button on the screen
    void drawButton(sf::RenderWindow &gameInstance);

    /// Takes a Vector2f (a pair of floats) as paramater and changes the position of the button
    void setPos(sf::Vector2f poz);

};


#endif //OOP_BUTTON_H
