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

    std::string color;

    int prop_price, house_price, id_proprietar, nr_case;

    sf::Texture texture;

    std::vector<int> rent;


public:


    explicit Property(std::string color = "",
                      int prop_price = 0,
                      int house_price = 0,
                      int id = 0,
                      std::vector<int> rent = {0, 0, 0, 0, 0, 0},
                      int nr_case = 0);

    Property(const Property &p);

    Property &operator=(const Property &other);

    [[nodiscard]] int price() const;/// Returns the price to buy the property

    void set_prop(int id);/// Changes the owner of the property

    [[nodiscard]] int id() const;/// Returns the id of the owner

    [[nodiscard]] int houses() const;/// Returns the number of houses built on the property

    int out_rent(int nr);/// Returns the rent amount if nr houses are built on the property

    [[nodiscard]] int out_house_price() const;/// Returns the price to build a house

    void inc_houses();/// Increases the number of houses built on the property

    sf::Sprite getSprite() override;/// Loads the coresponding texture and transforms it into a sprite returning it

    [[nodiscard]] int
    is_buyable() override;/// Returns if the property can be bougth (1 if it can be / 0 if it can't be)

    Square *clone() const override;/// Returns a pointer to an identical property
};


#endif //OOP_PROPERTY_H
