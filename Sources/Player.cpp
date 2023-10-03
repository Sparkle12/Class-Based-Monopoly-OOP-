//
// Created by Adi on 5/16/2023.
//

#include "../Headers/Player.h"

Player::Player(int player_id, int money, int poz, std::vector<Property *> proprietati) : money(money),
                                                                                         player_id(player_id),
                                                                                         pozitie(poz),
                                                                                         proprietati(std::move(
                                                                                                 proprietati)) {}

Player::Player(const Player &p) {

    if (this != &p) {
        this->pozitie = p.pozitie;
        this->player_id = p.player_id;
        this->money = p.money;
        this->texture = p.texture;

        for (Property *i: p.proprietati) {
            this->proprietati.emplace_back(new Property(*i));
        }

    }

}

Player &Player::operator=(const Player &p) {

    pozitie = p.pozitie;
    money = p.money;
    player_id = p.player_id;
    texture = p.texture;
    charges = p.charges;

    for (Property *i: p.proprietati) {
        proprietati.emplace_back(new Property(*i));
    }

    return *this;
}

Player::~Player() {

    for (Property *i: proprietati) {
        i = nullptr;
        delete i;
    }
}

/// Takes an integer as a parameter and returns the a pointer to the i-th property owned by the player (index starts at 0)
Property *Player::operator[](int i) {

    return this->proprietati[i];
}

/// Takes a refference to a Board a object and integer (default is 0) rolls 2 six sided dice and moves the player that many tiles forward
/// If a step is given it moves the player that many tiles forward
void Player::move(Board &b, int step) {

    if (!step) {
        int s = 0;
        /// Rolling the dice (doing it 2 times instead of taking %12 to keep the probability of each value appearing the same)
        for (int i = 0; i < 2; i++)
            s += (1 + (rand() % 6));


        /// Checking if the player passed the Start tile and give him his salary
        if (pozitie + s >= b.size())
            this->add_money(100);

        pozitie = (pozitie + s) % b.size();
    } else {
        if (pozitie + step >= b.size())
            this->add_money(100);

        pozitie = (pozitie + step) % b.size();
    }
}

/// Takes and integer as a parameter and adds that amount of money to the player
void Player::add_money(int amount) {
    money += amount;
}

/// Tries to buy the tile the player is on and throws an error if it is impossible
void Player::buy(Board &b) {

    auto *p = dynamic_cast<Property *>(b[pozitie]);

    if (p) {
        if (!(b[pozitie]->is_buyable()))
            throw owned();

        else if (money < p->price())
            throw not_enough_money();

        else {
            this->add_money(-p->price());
            p->set_prop(player_id);
            proprietati.push_back(p);
        }
    }


}

/// Returns the position of the player as a integer (index on the board)
[[nodiscard]] int Player::position() const {
    return pozitie;
}

/// Returns the id of the player as an integer
[[nodiscard]] int Player::id() const {
    return player_id;
}

/// Takes a reference to a Player object and a reference to a Board object
/// Pays another player the rent money for the tile he is on
void Player::pay(Player &other, Board &b) {

    auto *p = dynamic_cast<Property *>(b[pozitie]);

    if (p) {
        this->add_money(-p->out_rent(p->houses()));
        other.add_money((*p).out_rent((*p).houses()));

    }
}

/// Takes a pointer to a Property object as a parameter and buys a house on that property if possible else throws an error
void Player::buy_house(Property *p) {

    if (p->houses() >= 5)
        throw max_no_houses();

    else if (money < p->out_house_price())
        throw not_enough_money();

    money -= p->out_house_price();
    p->inc_houses();
}


/// Takes a constant reference to an Effect object and reference to a Board object as parameter
/// It dose the effect of the tile given as parameter (Example: Chance draws a random card from a collection of 4 and dose its effect see Effect.h line 21)
void Player::do_effect(const Effect &e, Board &b) {

    /// See Effect.h line 18 for more information on effect_id
    int effect_id = e.id_effect();

    /// Handles luxury tax
    if (effect_id == 1) {
        this->add_money(-150);


    }
        /// Handles chance
    else if (effect_id == 2) {
        int card = rand() % 4;

        /// See Effect.h line 21 for more information on chance card numbers
        if (card == 0) {
            pozitie = 0;
            this->add_money(100);
        } else if (card == 1) {
            this->move(b, 5);
        } else if (card == 2) {
            this->add_money(50);
        } else if (card == 3) {
            this->add_money(-100);
        }
    }
}

/// Return the sprite of the player
sf::Sprite Player::getSprite() {
    return sf::Sprite(texture);
}

/// Takes a reference to a sf::RenderWindow object and a reference to a Board object
/// Draws the player sprite on the screen
void Player::drawPlayer(sf::RenderWindow &gameInstance, Board &b) {

    sf::Vector2f pos;

    /// Calculating the position of the player relative to the tile he is on
    pos.x = b.get_sprite_at_position(pozitie).getPosition().x +
            float(b.get_sprite_at_position(pozitie).getTextureRect().getSize().x / 4.0 * (abs(player_id % 2 - 1)));

    pos.y = float(gameInstance.getSize().y / 2.0) +
            float(b.get_sprite_at_position(pozitie).getTextureRect().getSize().y / 4.0 * (player_id > 2));

    /// Setting the position and drawing the player
    sf::Sprite sprite = this->getSprite();
    sprite.setPosition(pos);
    gameInstance.draw(sprite);
}

/// Takes a sf::IntRect as a parameter and loads the texture inside of it
void Player::setTexture(sf::IntRect uvRect) {

    texture.loadFromFile(
            "Textures/PlayerSprites/dinoCharactersVersion1.1/sheets/DinoSprites - " + std::to_string(player_id) +
            ".png", uvRect);
}

/// Returns the vector containg the propertys the player owns as Property*
std::vector<Property *> Player::getProps() {
    return proprietati;
}

/// Returns how much money the player has
int Player::getMoney() const {
    return money;
}

/// Takes an integer as a paramter and sets the number of ability charges to that amount (default is 1)
void Player::set_charges(int x) {
    charges = x;
}

/// Returns how many ability charges the player has left
int Player::get_charges() const {
    return charges;
}




