#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "Headers/Game.h"

class Mage : public Player {
public:

    Mage(int playerId, int money, int poz, const std::vector<Property *> &proprietati = {}) : Player(playerId,
                                                                                                     money,
                                                                                                     poz,
                                                                                                     proprietati) {}

    void do_ability_on_board_targeted(Player *target, Board &b) override {
        if (this->get_charges()) {
            target->move(b, -2);
            this->set_charges(this->get_charges() - 1);
        } else
            throw out_of_charges();
    }

};

int main() {
    srand(time(nullptr));
    sf::RenderWindow window(sf::VideoMode(1712, 800), "Monopoly");
    std::vector<Player *> jucatori = {new Banker(1, 500, 0), new Thief(2, 500, 0)};
    Game game(jucatori);
    game.play(window);
    return 0;
}