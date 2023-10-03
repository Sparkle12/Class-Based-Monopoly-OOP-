//
// Created by Adi on 5/16/2023.
//

#ifndef OOP_PLAYERCLASESS_H
#define OOP_PLAYERCLASESS_H

#include "Player.h"

/// Each class has a unique ability
/// Bankers gain 200$ (1 charge per game)
/// Thiefs steal 100$ from another player (1 charge per game)
/// Mages cand move another player 2 tiles back (3 charges per game)

class Banker : public Player {
public:

    Banker(int playerId, int money, int poz, const std::vector<Property *> &proprietati = {}, int charges = 1);

    void do_ability_on_board_targeted(Player *target, Board &b) override;

};

class Thief : public Player {

public:

    Thief(int playerId, int money, int poz, const std::vector<Property *> &proprietati = {}, int charges = 1);

    void do_ability_on_board_targeted(Player *target, Board &b) override;

};

class Mage : public Player {

public:

    Mage(int playerId, int money, int poz, const std::vector<Property *> &proprietati = {}, int charges = 3);

    void do_ability_on_board_targeted(Player *target, Board &b) override;


};
#endif //OOP_PLAYERCLASESS_H
