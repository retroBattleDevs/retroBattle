#ifndef RandomMovement_H
#define RandomMovement_H

#include "headers/movements/Movement.h"

class RandomMovement : public Movement {
public:
    RandomMovement();
    virtual ~RandomMovement();

    virtual void movingPatern(Vec2d& pos, Vec2d& min, Vec2d& max, int moveAmountX, int moveAmountY) override;
protected:

private:
};

#endif // RandomMovement_H
