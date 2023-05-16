//
// Created by Adi on 5/16/2023.
//

#include "../Headers/Animation.h"

Animation::Animation(int start, int imageCount, float switchTime) : nrImage(imageCount),
                                                                    start(start),
                                                                    switchTime(switchTime) {
    currentImage = start;
    totalTime = 0.0f;
    uvRect.width = 72;
    uvRect.height = 72;
}

Animation::Animation(const Animation &a) : nrImage(a.nrImage), start(a.start), switchTime(a.switchTime) {}

void Animation::Update(float deltaTime) {
    totalTime += deltaTime;
    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentImage++;
    }
    if (currentImage >= start + nrImage)
        currentImage = start;
    uvRect.left = currentImage * uvRect.width;
    uvRect.top = 0;
}

[[nodiscard]] sf::IntRect Animation::get_uvRect() {
    return uvRect;
}