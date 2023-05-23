//
// Created by Adi on 5/16/2023.
//

#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "PlayerClasess.h"
#include "Board.h"
#include "Button.h"
#include "Animation.h"
#include "PropSelectMenu.h"
#include "Exceptions.h"

class Game {
    std::vector<Player *> jucatori = {new Banker(1, 500, 0), new Banker(2, 500, 0)};
    static Board defaultBoard;
    static const std::vector<std::string> texture_paths;
    std::vector<sf::Vector2f> pozitii = {sf::Vector2f(100, 600),
                                         sf::Vector2f(1300, 600),
                                         sf::Vector2f(1300, 600),
                                         sf::Vector2f(1000, 600),
                                         sf::Vector2f(400, 600),
                                         sf::Vector2f(700, 600)
    };
    std::vector<sf::Texture> texturi;
    std::vector<sf::Sprite> sprites;
    std::vector<Button> butoane;
    sf::Font font;
    sf::Text money;

public:

    Game();

    [[maybe_unused]] explicit Game(std::vector<Player *> players, const Board &b = defaultBoard);


    void play(sf::RenderWindow &window);


};


#endif //OOP_GAME_H
