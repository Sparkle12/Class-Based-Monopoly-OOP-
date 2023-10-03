//
// Created by Adi on 5/16/2023.
//
#include "../Headers/PlayerClasess.h"

/// Banker class ability gives the player 200$ (1 chearge per game)
void Banker::do_ability_on_board_targeted(Player *target, Board &b) {

    if (this->get_charges()) {
        this->add_money(200);
        this->set_charges(this->get_charges() - 1);
    } else
        throw out_of_charges();

}

Banker::Banker(int playerId, int money, int poz, const std::vector<Property *> &proprietati, int charges) : Player(
        playerId,
        money,
        poz,
        proprietati) {
    this->set_charges(charges);
}

/// Thief class ability steals 100$ from another player (1 charge per game)
void Thief::do_ability_on_board_targeted(Player *target, Board &b) {

    if (this->get_charges()) {
        this->add_money(100);
        target->add_money(-100);
        this->set_charges(this->get_charges() - 1);
        std::cout << target->getMoney() << std::endl;

    } else
        throw out_of_charges();
}

Thief::Thief(int playerId, int money, int poz, const std::vector<Property *> &proprietati, int charges) : Player(
        playerId,
        money,
        poz,
        proprietati) {
    this->set_charges(charges);
}

/// Mage class ability moves another player 2 tiles behind (3 charges per game)
void Mage::do_ability_on_board_targeted(Player *target, Board &b) {

    if (this->get_charges()) {
        target->move(b, -2);
        this->set_charges(this->get_charges() - 1);
    } else
        throw out_of_charges();
}


Mage::Mage(int playerId, int money, int poz, const std::vector<Property *> &proprietati, int charges) : Player(playerId,
                                                                                                               money,
                                                                                                               poz,
                                                                                                               proprietati) {
    this->set_charges(charges);
}