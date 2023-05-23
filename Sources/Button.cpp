//
// Created by Adi on 5/16/2023.
//

#include "../Headers/Button.h"

Button::Button(sf::Sprite hover, sf::Sprite nohover, sf::Vector2f pos) : Hover(std::move(hover)),
                                                                         noHover(std::move(nohover)),
                                                                         curentSprite(&noHover),
                                                                         position(pos) {}


Button::Button(const Button &bt) : Hover(bt.Hover), noHover(bt.noHover), curentSprite(&noHover),
                                   position(bt.position) {}

Button &Button::operator=(const Button &bt) {
    Hover = bt.Hover;
    noHover = bt.noHover;
    curentSprite = &noHover;
    position = bt.position;

    return *this;
}

bool Button::isHovered(sf::RenderWindow &gameInstance) {
    if (float(sf::Mouse::getPosition(gameInstance).x) > curentSprite->getGlobalBounds().left &&
        float(sf::Mouse::getPosition(gameInstance).x) <
        (curentSprite->getGlobalBounds().left + curentSprite->getGlobalBounds().width) &&
        float(sf::Mouse::getPosition(gameInstance).y) > curentSprite->getGlobalBounds().top &&
        float(sf::Mouse::getPosition(gameInstance).y) <
        (curentSprite->getGlobalBounds().top + curentSprite->getGlobalBounds().height)
            ) {
        curentSprite = &Hover;
        return true;
    } else {
        curentSprite = &noHover;
        return false;
    }
}

bool Button::checkClick(sf::RenderWindow &window) {
    if (this->isHovered(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        return true;
    else
        return false;
}

void Button::drawButton(sf::RenderWindow &gameInstance) {
    curentSprite->setPosition(position);
    gameInstance.draw(*curentSprite);
}

void Button::setPos(sf::Vector2f poz) {
    position = poz;
}

