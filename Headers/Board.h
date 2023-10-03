//
// Created by Adi on 5/16/2023.
//

#ifndef OOP_BOARD_H
#define OOP_BOARD_H

#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "Property.h"
#include "Effect.h"

class Board {
    // TABLA ESTE UN VECTOR DE PROPRIETATI SI EFECTE TABLA[i] TINUTE SUB FORMA DE Square*(trb fct dynamic_cast ca sa vezi daca e Property sau Effect) SCOATE ELEMENTUL DE PE POZITIA i DIN VECTOR

    std::vector<Square *> tabla = {new Effect(0),
                                   new Property("brown", 50, 25, 0, {5, 10, 15, 20, 25, 40}),
                                   new Property("brown", 60, 25, 0, {7, 12, 17, 22, 27, 50}),
                                   new Effect(2),
                                   new Effect(1),
                                   new Property("light_blue", 100, 50, 0, {8, 25, 50, 150, 250, 350}),
                                   new Property("magenta", 100, 50, 0, {8, 25, 50, 150, 250, 350}),
                                   new Property("orange", 100, 50, 0, {8, 25, 50, 150, 250, 350}),
                                   new Property("gold", 100, 50, 0, {8, 25, 50, 150, 250, 350}),
                                   new Property("green", 100, 50, 0, {8, 25, 150, 250, 350, 400}),
                                   new Property("dark_blue", 100, 50, 0, {8, 25, 50, 250, 350, 450}),
                                   new Property("red", 100, 50, 0, {8, 25, 50, 250, 350, 550})
    };
    /// The sprites for each tile
    std::vector<sf::Sprite> sprites;


    /// Index of each tile in the form of text
    /// They are displayed above each tile and are color coded
    /// White means the tile is buyable
    /// Yellow means the tile is an effect tile
    /// Red means the tile is owned by a bot
    /// Cyan means the tile is owned by the player
    std::vector<sf::Text> indici;
    sf::Font font;

public:

    Board();

    explicit Board(const std::vector<Square *> &tabla);


    [[maybe_unused]] Board(const Board &b);

    ~Board();

    Board &operator=(const Board &b);

    /// Takes and integer as a parameter and return the Square* at position i in the tabla vector
    Square *operator[](int i);

    /// Returns the number of the tiles that make up the board
    int size();

    /// Takes a render window as a parameter and draws the board and indexes on the screen
    void drawBoard(sf::RenderWindow &gameInstance);

    /// Takes a integer as a parameter and return the sprite at position i in the sprites vector (it coresponds to tile at operator[](i))
    sf::Sprite get_sprite_at_position(int i);

    /// Updates the color code of the indexes (See line 37 for more info)
    void updateIndici();


};


#endif //OOP_BOARD_H
