//
// Created by Adi on 5/16/2023.
//

#include "../Headers/Property.h"


Property::Property(std::string color, int prop_price, int house_price, int id, std::vector<int> rent, int nr_case)
        : color(std::move(color)),
          prop_price(prop_price),
          house_price(house_price),
          id_proprietar(id),
          nr_case(nr_case),
          rent(std::move(rent)) {}

Property::Property(const Property &p) : color(p.color),
                                        prop_price(p.prop_price),
                                        house_price(p.house_price),
                                        id_proprietar(p.id_proprietar),
                                        nr_case(p.nr_case),
                                        rent(p.rent) {}





Property &Property::operator=(const Property &other) {

    prop_price = other.prop_price;
    color = other.color;
    house_price = other.house_price;
    id_proprietar = other.id_proprietar;
    nr_case = other.nr_case;

    for (int i = 0; i < 6; i++)
        rent[i] = other.rent[i];

    return *this;

}

/// Returns the price to buy the property as a integer
[[nodiscard]] int Property::price() const {
    return prop_price;
}

/// Takes an integer as a parameter and changes the owner id to the one given as a parameter
void Property::set_prop(int id) {
    id_proprietar = id;
}

/// Returns the id of the owner as a integer
[[nodiscard]] int Property::id() const {
    return id_proprietar;
}

/// Returns the number of houses built on the property as an integer
[[nodiscard]] int Property::houses() const {
    return nr_case;
}

/// Takes an integer as a parameter and returns the rent that has to be paid if a player lands on the property with nr houses built
int Property::out_rent(int nr) {
    return rent[nr];
}

/// Returns the price to build a house on the property as an integer
[[nodiscard]] int Property::out_house_price() const {
    return house_price;
}

/// Increases the number of houses build on the property
void Property::inc_houses() {
    ++nr_case;
}

/// Loads the coresponding texture and returns the sprite of the property
sf::Sprite Property::getSprite() {

    texture.loadFromFile("Textures/" + color + ".png");

    return sf::Sprite(texture);
}

/// Returns if the property can be bought (1 if it can be / 0 if it can't be)
[[nodiscard]] int Property::is_buyable() {
    if (id_proprietar == 0)
        return 1;
    else
        return 0;
}

/// Returns a pointer to a new identical property
Square *Property::clone() const {
    return new Property(*this);
}