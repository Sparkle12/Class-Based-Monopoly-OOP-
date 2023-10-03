//
// Created by Adi on 5/16/2023.
//

#include "../Headers/Effect.h"


Effect::Effect(int effect_id) : effect_id(effect_id) {}

Effect::Effect(const Effect &e) : effect_id(e.effect_id) {}

Effect &Effect::operator=(const Effect &ef) {
    effect_id = ef.effect_id;
    return *this;
}
/// Returns the effect_id
[[nodiscard]] int Effect::id_effect() const {
    return effect_id;
}

/// Returns the sprite of the tile based on effect_id
sf::Sprite Effect::getSprite() {
    switch (effect_id) {

        case 0:
            texture.loadFromFile("Textures/Start.png");
            break;
        case 1:
            texture.loadFromFile("Textures/Tax.png");
            break;
        case 2:
            texture.loadFromFile("Textures/chance.png");
            break;
    }
    return sf::Sprite(texture);
}

/// Allways returns 0 as Effect tiles are not buyable by default
[[nodiscard]] int Effect::is_buyable() {
    return 0;
}

/// Clones the Effect tile it called on
Square *Effect::clone() const {
    return new Effect(*this);
}