//
// Created by Adi on 5/16/2023.
//

#include "../Headers/Player.h"

Player::Player(int player_id, int money, int poz, std::vector<Property *> proprietati) : money(money),
                                                                                         player_id(player_id),
                                                                                         pozitie(poz), proprietati(
                std::move(proprietati)) {}

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


Property *Player::operator[](int i) {
    //RETURNEAZA POINTER-UL SPRE PROPRIETATEA DE PE POZITIA I DIN VECTORUL PROPRIETATI
    return this->proprietati[i];
}

void Player::move(Board &b, int step) {
    //SIMULEAZA 2 ARUNCARI DE ZAR CU 6 FETE SI MUTA JUCATORUL SUMA CELOR 2 ARUNCARI PATRATE AVAND GRIJA SA RAMANA PE TABLA
    if (!step) {
        int s = 0;
        for (int i = 0; i < 2; i++)
            s += (1 + (rand() % 6));
        if (pozitie + s >= b.size())
            this->add_money(100);
        pozitie = (pozitie + s) % b.size();
    } else {
        if (pozitie + step >= b.size())
            this->add_money(1);
        pozitie = (pozitie + step) % b.size();
    }
}

void Player::add_money(int amount) {
    money += amount;
}

void Player::buy(Board &b) {
    //CUMPARA PROPRIETATEA PE CARE JUCATORUL SE AFLA
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


[[nodiscard]] int Player::position() const {
    //RETURNEAZA POZITIA
    return pozitie;
}


[[nodiscard]] int Player::id() const {
    //RETURNEAZA IDENTIFICATORUL JUCATORULUI
    return player_id;
}

void Player::pay(Player &other, Board &b) {
    //PLATESTE UNUI ALT JUCATOR CHIRIA PENTRU PROPRIETATEA PE CARE SE AFLA
    auto *p = dynamic_cast<Property *>(b[pozitie]);
    if (p) {
        this->add_money(-p->out_rent(p->houses()));
        other.add_money((*p).out_rent((*p).houses()));

    }
}

void Player::buy_house(Property *p) {
    //CUMPARA O CASA PE PROPRIETATEA DATA CA ARGUMENT
    if (p->houses() >= 5)
        throw max_no_houses();
    else if (money < p->out_house_price())
        throw not_enough_money();
    money -= p->out_house_price();
    p->inc_houses();
}

void Player::do_effect(const Effect &e, Board &b) {
    int effect_id = e.id_effect();

    if (effect_id == 1) {
        this->add_money(-150); //SCADE BANII DE LA LUXURY TAX
        std::cout << "Luxury Tax, pay 150$" << std::endl;
    } else if (effect_id == 2) {
        //                         0                 1                   2         3
        //carti_posibile = {"Move to start","Move 5 square forward","Gain 50$","Pay 100$"}
        int carte = rand() % 4;
        if (carte == 0) {
            pozitie = 0;
            this->add_money(100);
            std::cout << "Move to start gain 100" << std::endl;
        } else if (carte == 1) {
            this->move(b, 5);
            std::cout << "Move 5 squares forward" << std::endl;
        } else if (carte == 2) {
            this->add_money(50);
            std::cout << "Gain 50$" << std::endl;
        } else if (carte == 3) {
            this->add_money(-100);
            std::cout << "Pay 100$" << std::endl;
        }
    }
}

sf::Sprite Player::getSprite() {
    return sf::Sprite(texture);
}

void Player::drawPlayer(sf::RenderWindow &gameInstance, Board &b) {
    sf::Vector2f pos;

    pos.x = b.get_sprite_at_position(pozitie).getPosition().x +
            float(b.get_sprite_at_position(pozitie).getTextureRect().getSize().x / 4.0 * (abs(player_id % 2 - 1)));

    pos.y = float(gameInstance.getSize().y / 2.0) +
            float(b.get_sprite_at_position(pozitie).getTextureRect().getSize().y / 4.0 * (player_id > 2));


    sf::Sprite sprite = this->getSprite();
    sprite.setPosition(pos);
    gameInstance.draw(sprite);
}

void Player::setTexture(sf::IntRect uvRect) {
    texture.loadFromFile(
            "Textures/PlayerSprites/dinoCharactersVersion1.1/sheets/DinoSprites - " + std::to_string(player_id) +
            ".png", uvRect);
}

std::vector<Property *> Player::getProps() {
    return proprietati;
}

int Player::getMoney() const {
    return money;
}

void Player::set_charges(int x) {
    charges = x;
}

int Player::get_charges() {
    return charges;
}