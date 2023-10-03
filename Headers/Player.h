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

    int money, player_id, pozitie, charges = 1;

    sf::Texture texture;

    std::vector<Property *> proprietati;

public:

    explicit Player(int player_id = 0, int money = 0, int poz = 0, std::vector<Property *> proprietati = {});

    Player(const Player &p);


    Player &operator=(const Player &p);


    virtual ~Player();

    Property *operator[](int i); /// Returns the Property* of the i-th property the player owns (index starts at 0)

    void move(Board &b, int step = 0);/// Moves the player by specified amount (step) or by rolling 2 six sided dice

    void add_money(int amount);/// Gives the player the amount of money given as parameter

    void
    buy(Board &b);/// Tries to buy the tile the player is on if not able throws error (see Exceptions.h for more info on errors)

    [[nodiscard]] int position() const;/// Returns the position on the board of the player

    [[nodiscard]] int id() const;/// Returns the id of the player

    void pay(Player &other, Board &b);/// Pays another player the rent of the tile he is on

    void buy_house(
            Property *p);/// Tries to buy a house on the property given as parameter if not able throws error (see Exceptions.h for more info on errors)

    void do_effect(const Effect &e, Board &b);/// Dose the effect of the tile given as parameter

    sf::Sprite getSprite();/// Returns the sprite of the player made from the player texture

    void drawPlayer(sf::RenderWindow &gameInstance, Board &b);/// Draws the player on the screen

    void setTexture(
            sf::IntRect uvRect);/// Sets the texture that is inside the boundries given as parameter as the player texture

    std::vector<Property *> getProps(); /// Returns a vector of all the propertys the player owns

    int getMoney() const;/// Returns the amount of money the player has

    /// Virtual function that handles the abilities of different classes (See PlayerClasess.h for more info)
    [[maybe_unused]] virtual void
    do_ability_on_board_targeted([[maybe_unused]] Player *target, [[maybe_unused]] Board &b) = 0;

    [[maybe_unused]] void set_charges(int x);/// Sets the available ability charges to the amount given as parameter

    [[maybe_unused]] int get_charges() const;/// Returns how many charges the player has left

};


#endif //OOP_PLAYER_H
