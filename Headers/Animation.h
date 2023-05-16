//
// Created by Adi on 5/16/2023.
//

#ifndef OOP_ANIMATION_H
#define OOP_ANIMATION_H

#include "SFML/Graphics.hpp"
#include <iostream>

class Animation {
    int nrImage;
    int currentImage{};
    int start;
    sf::IntRect uvRect;

    float totalTime{};
    float switchTime;

public:
    Animation(int start, int imageCount, float switchTime);

    Animation(const Animation &a);

    void Update(float deltaTime);

    [[nodiscard]] sf::IntRect get_uvRect();
};


#endif //OOP_ANIMATION_H
