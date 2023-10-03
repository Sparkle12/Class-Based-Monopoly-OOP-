//
// Created by Adi on 5/16/2023.
//

#include "../Headers/PropSelectMenu.h"
#include "../Headers/Player.h"

PropSelectMenu::PropSelectMenu(const std::vector<Property *> &proprietati) {
    /// Reserving space for 100 butons and 100 texts (see PropSelectMenu.h line 14 for more info on texts)
    /// I am reserving the space because SFML dosent copy sprites well and the vector would resize the sprites would corrupt
    butoane_proprietati.reserve(100);
    nr_house.reserve(100);

    font.loadFromFile("Fonts/MinimalPixel v2.ttf");

    for (Property *i: proprietati) {
        /// Making the buttons from the sprite of each property owned by the player and the texts from the number of houses built on them
        butoane_proprietati.emplace_back(i->getSprite(), i->getSprite(), sf::Vector2f(50, 50));
        nr_house.emplace_back("X" + std::to_string(i->houses()), font, 36);
    }

    /// Making exit button
    exit1.loadFromFile("Textures/exit-hover.png");
    exit2.loadFromFile("Textures/exit-nohover.png");
    butoane_proprietati.emplace_back(sf::Sprite(exit1), sf::Sprite(exit2), sf::Vector2f(0, 0));

    for (sf::Text txt: nr_house)
        txt.setFillColor(sf::Color::White);
}

PropSelectMenu::PropSelectMenu(const PropSelectMenu &menu) : butoane_proprietati(menu.butoane_proprietati) {}

/// Takes an integer as a parameter and returns the i-th button in the menu (index starts at 0 and the exit button is the last one)
Button PropSelectMenu::operator[](int i) {
    return this->butoane_proprietati[i];
}

/// Returns the number of buttons present in the menu (including the exit button)
int PropSelectMenu::size() {
    return int(butoane_proprietati.size());
}

/// Takes a reference to a sf::RenderWindow object and draws the menu on the screen
void PropSelectMenu::drawMenu(sf::RenderWindow &window) {

    sf::Vector2f poz(50, 50); /// The position of the first property button
    window.clear(sf::Color::Black);

    for (int i = 0; i < int(butoane_proprietati.size() - 1); i++) {
        /// Setting the position of the property button and the text
        nr_house[i].setPosition(poz + sf::Vector2f(20, 148));
        butoane_proprietati[i].setPos(poz);

        /// Drawing the property button and the text
        butoane_proprietati[i].drawButton(window);
        window.draw(nr_house[i]);

        /// if there is enough space to fit the next button it is placed on the same row if not it is placed on the next row
        if (poz.x + 250 < float(window.getSize().x))
            poz += sf::Vector2f(150, 0);
        else
            poz += sf::Vector2f(0, 150);
    }

    /// Setting the position and checking if the exit button is hovered before drawing it on the screen
    butoane_proprietati[butoane_proprietati.size() - 1].setPos(
            sf::Vector2f(float(window.getSize().x / 2.0 - 105), 600));
    butoane_proprietati[butoane_proprietati.size() - 1].isHovered(window);
    butoane_proprietati[butoane_proprietati.size() - 1].drawButton(window);

}

/// Checks what button has pressed and handles the logic behind them
void PropSelectMenu::checkClick(sf::RenderWindow &window, sf::Event &event, std::vector<Player *> jucatori,
                                int &in_buy_house_menu) {

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        /// If a property button has been clicked it tries to buy a house on said property
        /// If it is impossible it throws a error
        for (int i = 0; i < this->size() - 1; i++) {
            if (this->operator[](i).checkClick(window)) {
                try {
                    jucatori[0]->buy_house((*jucatori[0])[i]);
                }
                catch (game_error &error) {
                    std::cout << error.what() << std::endl;
                }
            }
        }

        /// If the exit button is pressed it goes back to the main screen
        if (this->operator[](this->size() - 1).checkClick(window))
            in_buy_house_menu = 0;
    }
}