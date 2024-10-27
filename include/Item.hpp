#pragma once
#include <string>
#include "GameObject.hpp"

class Item : public GameObject
{
private:
    std::string name;
    char symbol;
    int weight;
    bool isUsable;

public:
    Item(std::string name, int weight, bool isUsable, char symbol, int x, int y);
    ~Item() = default;

    virtual void use() = 0;

    std::string getName();
    char getSymbol() const;
    int getWeight();
    bool getIsUsable();

    void setName(std::string name);
    void setSymbol(char symbol);
};