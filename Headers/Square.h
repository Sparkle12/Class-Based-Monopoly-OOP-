//
// Created by Adi on 5/16/2023.
//

#ifndef OOP_SQUARE_H
#define OOP_SQUARE_H

#include "SFML/Graphics.hpp"

class Square {
    /// Pure virtual class that is the parent class of the Property and Effect classes
    /// Mostly used to be able to hold both Property and Effect objects in the same vector


public:

    virtual sf::Sprite getSprite() = 0;

    virtual int is_buyable() = 0;

    virtual Square *clone() const = 0;

    virtual ~Square() = default;
};


#endif //OOP_SQUARE_H
