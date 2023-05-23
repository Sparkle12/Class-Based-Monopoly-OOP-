//
// Created by Adi on 5/16/2023.
//

#include "../Headers/Property.h"


Property::Property(std::string color, int prop_price, int house_price, int id, std::vector<int> rent, int nr_case)
        : color(std::move(color)), prop_price(prop_price), house_price(house_price), id_proprietar(id),
          nr_case(nr_case), rent(std::move(rent)) {}

Property::Property(const Property &p) : color(p.color), prop_price(p.prop_price), house_price(p.house_price),
                                        id_proprietar(p.id_proprietar),
                                        nr_case(p.nr_case), rent(p.rent) {}

/*
Property::friend std::ostream& operator<<(std::ostream& out,const Property& sq)
{
    out<<"["<<sq.color<<","<<sq.prop_price<<","<<sq.house_price<<","<<sq.id_proprietar<<","<<sq.nr_case<<",[";
    for(int i =0;i<6;i++)
        if(i != 5)
            out<<sq.rent[i]<<",";
        else
            out<<sq.rent[i]<<"]";
    out<<"]";

    return out;
}
*/

/*
Property::friend std::istream& operator>>(std::istream& in, Property& sq)
{
    in>>sq.color>>sq.prop_price>>sq.house_price>>sq.id_proprietar;
    for(int i = 0;i<6;i++)
        in>>sq.rent[i];
    return in;
}*/



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


[[nodiscard]] int Property::price() const {
    //RETURNEAZA PRETUL PROPRIETATII
    return prop_price;
}


void Property::set_prop(int id) {
    //SCHIMBA PROPRIETARUL PROPRIETATII
    id_proprietar = id;
}


[[nodiscard]] int Property::id() const {
    //RETURNEAZA PROPRIETARUL PROPRIETATII
    return id_proprietar;
}


[[nodiscard]] int Property::houses() const {
    //RETURNEAZA NUMARUL DE CASE DE PE PROPRIETATE
    return nr_case;
}


int Property::out_rent(int nr) {
    //RETURNEAZA SUMA DE PLATIT CA SI CHIRIE CU UN ANUMIT NUMAR DE CASE PE PROPRIETATE
    return rent[nr];
}


[[nodiscard]] int Property::out_house_price() const {
    //RETURNEAZA PRETUL UNEI CASE
    return house_price;
}

void Property::inc_houses() {
    //INCREMENTEAZA NUMARUL DE CASE
    ++nr_case;
}

sf::Sprite Property::getSprite() {

    texture.loadFromFile("Textures/" + color + ".png");

    return sf::Sprite(texture);
}

[[nodiscard]] int Property::is_buyable() {
    if (id_proprietar == 0)
        return 1;
    else
        return 0;
}

Square *Property::clone() const {
    return new Property(*this);
}