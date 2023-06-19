//
// Created by Adi on 5/16/2023.
//

#ifndef OOP_PLAYERCLASESS_H
#define OOP_PLAYERCLASESS_H

#include "Player.h"

class Banker : public Player {
public:

    Banker(int playerId, int money, int poz, const std::vector<Property *> &proprietati = {}, int charges = 1);

    void do_ability_on_board_targeted(Player target, Board b) override;

};

class Thief : public Player {

public:

    Thief(int playerId, int money, int poz, const std::vector<Property *> &proprietati = {}, int charges = 1);

    void do_ability_on_board_targeted(Player *target, Board b) override;

};


#endif //OOP_PLAYERCLASESS_H
