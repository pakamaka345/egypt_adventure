#pragma once
#include <string>

class Entity
{
private:
    char symbol;
    std::string name;
    int health;
    int strength;

public:
    Entity(std::string name, int health, int strength, char symbol);
    virtual ~Entity() = default;

    virtual void draw() const = 0;
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

