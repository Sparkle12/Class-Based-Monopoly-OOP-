//
// Created by Adi on 5/16/2023.
//

#include "../Headers/Board.h"

Board::Board() {

    int count = 1;

    /// Making the sprites for each tile in the board and the indexes (See Board.h line 37 for more information on the indexing)
    for (Square *Tile: tabla) {
        font.loadFromFile("Fonts/MinimalPixel v2.ttf");
        sprites.emplace_back(Tile->getSprite());
        indici.emplace_back(std::to_string(count), font, 36);
        count++;
    }
}


[[maybe_unused]] Board::Board(const Board &b) : sprites(b.sprites), indici(b.indici), font(b.font) {

    std::vector<Square *> temp;

    /// Cloning each tile and then assing it to the Square* vector
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

    /// Cloning the board, sprites and indexes and then assing them to the new board
    for (Square *i: b.tabla) {
        temp.emplace_back(i->clone());
        temp2.emplace_back(i->getSprite());
        temp3.emplace_back(std::to_string(count), font, 36);
        count++;
    }
    tabla.swap(temp);
    sprites = temp2;
    font = b.font;
    indici = temp3;

    return *this;
}


/// Returns the Square* at position i in the tabla vector
Square *Board::operator[](int i) {
    return this->tabla[i];
}

/// Returns the number of Tiles that form the board
int Board::size() {
    return int(tabla.size());
}

void Board::drawBoard(sf::RenderWindow &gameInstance) {

    float offset = 0;

    for (int i = 0; i < int(sprites.size()); i++) {
        /// Setting the position for the sprite and index of tile i
        sprites[i].setPosition(offset, float(gameInstance.getSize().y / 2.0));
        indici[i].setPosition(offset, float(gameInstance.getSize().y / 2.0 - 30));

        /// Drawing the sprite and index
        gameInstance.draw(sprites[i]);
        gameInstance.draw(indici[i]);

        /// Increasing the offset so the next tile lands next to the one just drawn
        offset += float(sprites[i].getTextureRect().getSize().x);
    }

}

/// Returns the sprite of the tile at position i in the sprites vector
sf::Sprite Board::get_sprite_at_position(int i) {
    return sprites[i];
}

/// Updates the indexes so they match the color code (See Board.h line 37 for more information on the indexing)
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
