//
// Created by Adi on 5/16/2023.
//

#include "../Headers/Button.h"

Button::Button(sf::Sprite hover, sf::Sprite nohover, sf::Vector2f pos) : Hover(std::move(hover)),
                                                                         noHover(std::move(nohover)),
                                                                         curentSprite(&noHover),
                                                                         position(pos) {}


Button::Button(const Button &bt) : Hover(bt.Hover),
                                   noHover(bt.noHover),
                                   curentSprite(&noHover),
                                   position(bt.position) {}

Button &Button::operator=(const Button &bt) {

    Hover = bt.Hover;
    noHover = bt.noHover;
    curentSprite = &noHover;
    position = bt.position;

    return *this;
}

bool Button::isHovered(sf::RenderWindow &gameInstance) {
    /// Checking if the mouse is inside the boudaries of the sprite
    if (float(sf::Mouse::getPosition(gameInstance).x) > curentSprite->getGlobalBounds().left &&
        float(sf::Mouse::getPosition(gameInstance).x) <
        (curentSprite->getGlobalBounds().left + curentSprite->getGlobalBounds().width) &&
        float(sf::Mouse::getPosition(gameInstance).y) > curentSprite->getGlobalBounds().top &&
        float(sf::Mouse::getPosition(gameInstance).y) <
        (curentSprite->getGlobalBounds().top + curentSprite->getGlobalBounds().height)
            ) {
        /// Changing the display sprite to the hovered one and return true
        curentSprite = &Hover;
        return true;
    } else {
        /// Changing the display sprite to the not hovered one and return false
        curentSprite = &noHover;
        return false;
    }
}

bool Button::checkClick(sf::RenderWindow &window) {
    /// Checking if the button is hovered and left click is pressed and returning true or false
    if (this->isHovered(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        return true;
    else
        return false;
}

void Button::drawButton(sf::RenderWindow &gameInstance) {
    /// Setting the position and drawing the button
    curentSprite->setPosition(position);
    gameInstance.draw(*curentSprite);
}

/// Changes the position of the button
void Button::setPos(sf::Vector2f poz) {
    position = poz;
}

