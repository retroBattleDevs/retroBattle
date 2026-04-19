#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

class RandomNumberGenerator {
    public:
        virtual ~RandomNumberGenerator() = default;
        virtual int getRandomNumber(int min, int max) = 0;

    protected:

    private:
};

#endif // RANDOMNUMBERGENERATOR_H