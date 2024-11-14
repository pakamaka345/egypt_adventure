#pragma once
#include <string>
#include "GameObject.hpp"

class Entity : public GameObject
{
private:
    char symbol;
    std::string name;
    int health;
    int strength;

public:
    Entity(std::string name, int health, int strength, char symbol, int x, int y);
    virtual ~Entity() = default;

    virtual void attack(Entity& target) = 0;

    std::string getName() const;
    void setName(std::string name);

    char getSymbol() const;
    void setSymbol(char symbol);

    int getHealth() const;
    void setHealth(int health);

    int getStrength() const;
    void setStrength(int strength);

    bool isAlive() const;
};

