#include "headers/movements/Movement.h"

Movement::Movement() {}

Movement::~Movement() {}

std::string Movement::getTypeName() const {
    return movementName;
}
