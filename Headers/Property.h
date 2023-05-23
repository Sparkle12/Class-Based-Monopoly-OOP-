//
// Created by Adi on 5/16/2023.
//

#ifndef OOP_PROPERTY_H
#define OOP_PROPERTY_H

#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "Square.h"

class Property : public Square {
    //PROPRIETATILE AU O CULOARE(APARTENENTA LA CARTIERE PE VIITOR),UN PRET DE ACHIZITIE,UN PRET PT CASE,UN ID DE PROPRIETAR SI UN VECTOR PT CHIRIILE PT FIECARE NUMAR DE CASE UNDE rent[nr_case] ESTE CHIRIA PT NUMARU ACELA DE CASE

    std::string color;
    int prop_price, house_price, id_proprietar, nr_case;
    sf::Texture texture;

    std::vector<int> rent;


public:


    explicit Property(std::string color = "", int prop_price = 0, int house_price = 0, int id = 0,
                      std::vector<int> rent = {0, 0, 0, 0, 0, 0}, int nr_case = 0);

    Property(const Property &p);

    //friend std::ostream& operator<<(std::ostream& out,const Property& sq);



    //friend std::istream& operator>>(std::istream& in, Property& sq);



    Property &operator=(const Property &other);


    [[nodiscard]] int price() const;


    void set_prop(int id);


    [[nodiscard]] int id() const;


    [[nodiscard]] int houses() const;


    int out_rent(int nr);

    [[nodiscard]] int out_house_price() const;

    void inc_houses();

    sf::Sprite getSprite() override;

    [[nodiscard]] int is_buyable() override;

    Square *clone() const override;
};


#endif //OOP_PROPERTY_H
