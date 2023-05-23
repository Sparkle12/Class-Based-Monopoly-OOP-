//
// Created by Adi on 5/16/2023.
//

#include "../Headers/Effect.h"


Effect::Effect(int effect_id) : effect_id(effect_id) {}

Effect::Effect(const Effect &e) : effect_id(e.effect_id) {}

/*
friend ostream& operator<<(ostream& out,const Effect& ef)
{
    out<<ef.effect_id;
    return out;
}


friend istream& operator>>(istream& in,Effect& ef)
{
    in>>ef.effect_id;
    return in;
}
*/

Effect &Effect::operator=(const Effect &ef) {
    effect_id = ef.effect_id;
    return *this;
}

[[nodiscard]] int Effect::id_effect() const {
    return effect_id;
}

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

[[nodiscard]] int Effect::is_buyable() {
    return 0;
}

Square *Effect::clone() const {
    return new Effect(*this);
}