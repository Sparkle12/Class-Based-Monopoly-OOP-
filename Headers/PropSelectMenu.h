//
// Created by Adi on 5/16/2023.
//

#ifndef OOP_PROPSELECTMENU_H
#define OOP_PROPSELECTMENU_H

#include <iostream>
#include "Button.h"
#include "Property.h"
#include "Player.h"


/// nr_house is a vector of text that tells us how many houses are built on each property owned by the player

class PropSelectMenu {

    std::vector<Button> butoane_proprietati = {};
    sf::Texture exit1, exit2;
    sf::Font font;
    std::vector<sf::Text> nr_house;

public:

    explicit PropSelectMenu(const std::vector<Property *> &proprietati);

    PropSelectMenu(const PropSelectMenu &menu);

    Button operator[](int i);/// Returns the i-th button in the menu

    int size();/// Returns the number of buttons in the menu

    void drawMenu(sf::RenderWindow &window);/// Draws the menu on the screen

    /// Checks what button has been clicked and handles the logic behind it
    void checkClick(sf::RenderWindow &window, sf::Event &event, std::vector<Player *> jucatori, int &in_buy_house_menu);

};


#endif //OOP_PROPSELECTMENU_H
