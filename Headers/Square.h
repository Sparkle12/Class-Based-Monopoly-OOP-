//
// Created by Adi on 5/16/2023.
//

#ifndef OOP_SQUARE_H
#define OOP_SQUARE_H

#include "SFML/Graphics.hpp"

class Square {
    //CLASA SQUARE ESTE FACUTA PT A FI MOSTENITA DE PROPERTY SI EFFECT PENTRU A FACE POSIBILA MEMORAREA LOR INTR-UN SINGUR VECTOR CA Square*


public:

    virtual sf::Sprite getSprite() = 0;

    virtual int is_buyable() = 0;

    virtual ~Square() = default;
};


#endif //OOP_SQUARE_H
