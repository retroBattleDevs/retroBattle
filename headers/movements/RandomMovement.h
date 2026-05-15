#ifndef RandomMovement_H
#define RandomMovement_H

#include "headers/movements/Movement.h"

#include "headers/Entity.h"

class RandomMovement : public Movement {
public:
    RandomMovement();
    virtual ~RandomMovement();

    virtual void movingPatern(Vec2d& pos, Vec2d& min, Vec2d& max, int moveAmountX, int moveAmountY) override;

	int tempo;
protected:

private:
    void initializeWalkable();
	int maxWidth;
	int maxHeight;
	int minWidth;
	int minHeight;
};

#endif // RandomMovement_H
