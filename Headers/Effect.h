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
    // EFECTELE(AU UN ID UNDE possible_effects[id] ESTE FUNCTIONALITAETA PATRATULUI) SUNT ORICE PATRAT CE NU ESTE PROPRIETATE AKA START LUXURY TAX ETC..(MOMENTAN NU AI IMPLEMENTAT NIMIC AICI)

    //                       0        1            2       3
    // possible_effects = {"Start","Luxury Tax","Chance","Prison"}; , DE IMPLEMENTAT PRISON


    int effect_id;
    sf::Texture texture;

public:


    explicit Effect(int effect_id = 0);

    Effect(const Effect &e);

/*
    friend ostream& operator<<(ostream& out,const Effect& ef)
    {
        out<<ef.effect_id;
        return out;
    }


    friend istream& operator>>(istream& in,Effect& ef)
    {
        in>>ef.effect_id;
        return in;
    }
   */

    Effect &operator=(const Effect &ef);

    [[nodiscard]] int id_effect() const;

    sf::Sprite getSprite() override;

    [[nodiscard]] int is_buyable() override;

};


#endif //OOP_EFFECT_H
