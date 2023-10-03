#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "Headers/Game.h"



int main() {

    srand(time(nullptr));

    sf::RenderWindow window(sf::VideoMode(1712, 800), "Monopoly");

    std::vector<Player *> jucatori = {new Banker(1, 500, 0), new Thief(2, 500, 0)};

    Game game(jucatori);
    game.play(window);
    return 0;
}