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


[[maybe_unused]] Board::Board(const Board &b) : sprites(b.sprites), indici(b.indici), font(b.font) {

    std::vector<Square *> temp;

    for (Square *i: b.tabla) {

        temp.emplace_back(i->clone());
    }

    tabla = temp;
}

Board::~Board() {
    for (Square *i: tabla)
        delete i;

}

Board &Board::operator=(const Board &b) {
    int count = 1;
    std::vector<Square *> temp;
    std::vector<sf::Sprite> temp2;
    std::vector<sf::Text> temp3;
    for (Square *i: b.tabla) {
        temp.emplace_back(i->clone());
        temp2.emplace_back(i->getSprite());
        temp3.emplace_back(std::to_string(count), font, 36);
        count++;
    }
    tabla = temp;
    sprites = temp2;
    font = b.font;
    indici = temp3;
    return *this;
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
    std::cout << tabla.size() << std::endl;
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

Board::Board(const std::vector<Square *> &tabla) : tabla(tabla) {}
