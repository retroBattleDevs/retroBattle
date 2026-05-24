#pragma once
#include "headers/enemies/Enemy.h"

class Spider : public Enemy {
public:

    Spider(int id, const int width, const int height, Vec2d position);
    void drawSelf() const override;
};