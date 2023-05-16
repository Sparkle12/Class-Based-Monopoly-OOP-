//
// Created by Adi on 5/16/2023.
//

#include "../Headers/PropSelectMenu.h"

PropSelectMenu::PropSelectMenu(const std::vector<Property *> &proprietati) {
    butoane_proprietati.reserve(100);
    nr_house.reserve(100);
    font.loadFromFile("Fonts/MinimalPixel v2.ttf");
    for (Property *i: proprietati) {
        butoane_proprietati.emplace_back(i->getSprite(), i->getSprite(), sf::Vector2f(50, 50));
        nr_house.emplace_back("X" + std::to_string(i->houses()), font, 36);
    }
    exit1.loadFromFile("Textures/exit-hover.png");
    exit2.loadFromFile("Textures/exit-nohover.png");
    butoane_proprietati.emplace_back(sf::Sprite(exit1), sf::Sprite(exit2), sf::Vector2f(0, 0));
    for (sf::Text txt: nr_house)
        txt.setFillColor(sf::Color::White);
}

PropSelectMenu::PropSelectMenu(const PropSelectMenu &menu) : butoane_proprietati(menu.butoane_proprietati) {}

Button PropSelectMenu::operator[](int i) {

    return this->butoane_proprietati[i];
}

int PropSelectMenu::size() {
    return int(butoane_proprietati.size());
}

void PropSelectMenu::drawMenu(sf::RenderWindow &window) {
    sf::Vector2f poz(50, 50);
    window.clear(sf::Color::Black);
    for (int i = 0; i < int(butoane_proprietati.size() - 1); i++) {
        nr_house[i].setPosition(poz + sf::Vector2f(20, 148));
        butoane_proprietati[i].setPos(poz);
        butoane_proprietati[i].drawButton(window);
        window.draw(nr_house[i]);
        if (poz.x + 250 < float(window.getSize().x))
            poz += sf::Vector2f(150, 0);
        else
            poz += sf::Vector2f(0, 150);
    }
    butoane_proprietati[butoane_proprietati.size() - 1].setPos(
            sf::Vector2f(float(window.getSize().x / 2.0 - 105), 600));
    butoane_proprietati[butoane_proprietati.size() - 1].isHovered(window);
    butoane_proprietati[butoane_proprietati.size() - 1].drawButton(window);

}
