#pragma once
#include "headers/enemies/Enemy.h"

class Snake : public Enemy {
public:
    Snake(int id, const int width, const int height, Vec2d position);
    void drawSelf() const override;
};