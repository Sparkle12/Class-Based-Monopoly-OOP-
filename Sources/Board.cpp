//
// Created by Adi on 5/16/2023.
//

#include "../Headers/Board.h"

Board::Board() {
    int count = 1;
    for (Square *Tile: tabla) {
        font.loadFromFile("Fonts/MinimalPixel v2.ttf");
        sprites.emplace_back(Tile->getSprite());
        indici.emplace_back(std::to_string(count), font, 36);
        count++;
    }
}


Board::Board(const Board &b) : sprites(b.sprites) {
    for (Square *i: b.tabla) {

        auto *p = dynamic_cast<Property *>(i);
        if (p) {
            tabla.emplace_back(new Property(*p));
        } else {
            auto *e = dynamic_cast<Effect *>(i);
            if (e)
                tabla.emplace_back(new Effect(*e));
        }

    }
}

Board::~Board() {
    for (Square *i: tabla)
        delete i;

}

//Board &operator=(const Board &b) = default;
/*
friend ostream& operator<<(ostream& out,const Board& b)
{

    Effect* e;
    for(Square* i : b.tabla)
    {
        Property* p;
        if ((p = dynamic_cast<Property *>(i))) {
            out << *p << endl;
        } else {
            e = dynamic_cast<Effect *>(i);
            out << *e << endl;
        }
    }
    return out;
}
*/


Square *Board::operator[](int i) {
    //RETURNEAZA POINTER-UL DE SQUARE DE LA POZITIA I DIN TABLA
    return this->tabla[i];
}


int Board::size() {
    //RETURNEAZA NUMARUL DE PATRATE DIN TABLA
    return int(tabla.size());
}

void Board::drawBoard(sf::RenderWindow &gameInstance) {
    float offset = 0;
    for (int i = 0; i < int(sprites.size()); i++) {
        sprites[i].setPosition(offset, float(gameInstance.getSize().y / 2.0));
        indici[i].setPosition(offset, float(gameInstance.getSize().y / 2.0 - 30));
        gameInstance.draw(sprites[i]);
        gameInstance.draw(indici[i]);
        offset += float(sprites[i].getTextureRect().getSize().x);
    }

}

sf::Sprite Board::get_sprite_at_position(int i) {
    return sprites[i];
}

void Board::updateIndici() {
    for (int i = 0; i < int(tabla.size()); i++) {

        auto *p = dynamic_cast<Property *>(tabla[i]);
        if (p) {
            if (p->id() == 1)
                indici[i].setFillColor(sf::Color::Cyan);
            else if (p->id() != 0)
                indici[i].setFillColor(sf::Color::Red);
        } else
            indici[i].setFillColor(sf::Color::Yellow);

    }

}
