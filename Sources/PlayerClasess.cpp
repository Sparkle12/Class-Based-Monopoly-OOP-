//
// Created by Adi on 5/16/2023.
//

#include "../Headers/PlayerClasess.h"

void Banker::do_ability() {
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
        proprietati) { this->set_charges(charges); }

void Thief::do_ability_targeted(Player *target) {
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
        proprietati) { this->set_charges(charges); }
