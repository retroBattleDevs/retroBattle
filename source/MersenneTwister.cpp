#include "headers/MersenneTwister.h"

MersenneTwister::MersenneTwister() {
    engine = std::mt19937(std::random_device{}());
}

int MersenneTwister::getRandomNumber(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);

    return dist(engine);
}

std::mt19937 MersenneTwister::getEngine() const {
    return engine;
}