//
// Created by Adi on 5/16/2023.
//

#ifndef OOP_PROPSELECTMENU_H
#define OOP_PROPSELECTMENU_H

#include <iostream>
#include "Button.h"
#include "Property.h"

class PropSelectMenu {
    std::vector<Button> butoane_proprietati = {};
    sf::Texture exit1, exit2;
    sf::Font font;
    std::vector<sf::Text> nr_house;

public:

    explicit PropSelectMenu(const std::vector<Property *> &proprietati);

    PropSelectMenu(const PropSelectMenu &menu);

    Button operator[](int i);

    int size();

    void drawMenu(sf::RenderWindow &window);

};


#endif //OOP_PROPSELECTMENU_H
