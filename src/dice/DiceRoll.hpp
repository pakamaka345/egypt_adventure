#pragma once
#include <random>

class DiceRoll
{
public:
    DiceRoll() : generator(std::random_device{}()) {}
    explicit DiceRoll(int sides) : sides(sides), generator(std::random_device{}()) {}

    int roll() {
        std::uniform_int_distribution<int> distribution(1, sides);
        return distribution(generator);
    }

    int randomNumber(int min, int max)
    {
        std::uniform_int_distribution<int> dis(min, max);
        return dis(generator);
    }

private:
    int sides{};
    std::mt19937 generator;
};