#pragma once
#include "Entity.h"
class GateKeeper : public Entity {
public:
	GateKeeper();
	GateKeeper(int id, const int width, const int height, Vec2d position);

    //Rule of Five

    ~GateKeeper();
    GateKeeper(const GateKeeper& other);
    GateKeeper& operator=(const GateKeeper& other);
    GateKeeper(GateKeeper&& other) noexcept;
    GateKeeper& operator=(GateKeeper&& other) noexcept;

    //Override

    void drawSelf() const override;
    EntityTypes::Type getType() const override;
};
