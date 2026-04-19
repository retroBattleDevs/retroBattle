#ifndef MERSENNETWISTER_H
#define MERSENNETWISTER_H

#include "headers/RandomNumberGenerator.h"

#include <random>

class MersenneTwister : public RandomNumberGenerator {
    public:
        MersenneTwister();

        int getRandomNumber(int min, int max) override;
        std::mt19937 getEngine() const;

    private:
        std::mt19937 engine;
};

#endif // MERSENNETWISTER_H