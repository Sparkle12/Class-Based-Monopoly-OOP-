//
// Created by Adi on 5/16/2023.
//

#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "Property.h"
#include "Board.h"
#include "Exceptions.h"

class Player {
    // JUCATORUL ARE UN ID, POZITIE ,SUMA DE BANI SI UN VECTOR DE PROPRIETATI. EL SE POATE MUTA PE TABLA SI POATE CUMPARA PROPRIETATI(NU AI CHECK DACA ARE DESTUI BANI)
    int money, player_id, pozitie, charges = 1;

    sf::Texture texture;

    std::vector<Property *> proprietati;

public:

    explicit Player(int player_id = 0, int money = 0, int poz = 0, std::vector<Property *> proprietati = {});

    Player(const Player &p);


    //friend std::ostream &operator<<(std::ostream &out, const Player &p);



    Property *operator[](int i);

    void move(Board &b, int step = 0);


    void add_money(int amount);

    void buy(Board &b);


    [[nodiscard]] int position() const;


    [[nodiscard]] int id() const;

    void pay(Player &other, Board &b);

    void buy_house(Property *p);

    void do_effect(const Effect &e, Board &b);

    sf::Sprite getSprite();

    void drawPlayer(sf::RenderWindow &gameInstance, Board &b);

    void setTexture(sf::IntRect uvRect);

    std::vector<Property *> getProps();

    int getMoney() const;

    [[maybe_unused]] virtual void do_ability() {}

    [[maybe_unused]] virtual void do_ability_targeted(Player *target) {}

    [[maybe_unused]] virtual void do_ability_on_board(const Board &b) {}

    [[maybe_unused]] virtual void do_ability_on_board_targeted(Player *target, Board &b) {}

    void set_charges(int x);

    int get_charges();

};


#endif //OOP_PLAYER_H
