//
// Created by Adi on 5/16/2023.
//

#ifndef OOP_EFFECT_H
#define OOP_EFFECT_H

#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "Square.h"

class Effect : public Square {
    /// Effect tiles are that do something when landed on and are not buyable (See list below)
    /// Start has effect_id 0
    /// Tax has effect_id 1
    /// Chance has effect_id 2
    /// Posible chance outcomes:
    /// "Move to start" has card number 0
    /// "Move 5 tiles forward" has card number 1
    /// "Gain 50$" has card number 2
    /// "Pay 100$" has card number 3


    int effect_id;
    sf::Texture texture;

public:


    explicit Effect(int effect_id = 0);

    Effect(const Effect &e);

    Effect &operator=(const Effect &ef);

    [[nodiscard]] int id_effect() const; /// Returns the effect_id

    sf::Sprite getSprite() override; /// Returns the sprite of the tile

    [[nodiscard]] int is_buyable() override; /// Returns 0 allways because Effect tiles are not buyable buy default

    Square *
    clone() const override; /// Generates a Square* to an indentical Effect tile as the one the method is called on

};


#endif //OOP_EFFECT_H
