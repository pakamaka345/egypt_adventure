#pragma once
#include <string>

class Item
{
private:
    std::string name;
    char symbol;
    int weight;
    bool isUsable;

public:
    Item(std::string name, int weight, bool isUsable, char symbol);
    ~Item() = default;

    virtual void draw() = 0;

    virtual void use() = 0;

    std::string getName();
    char getSymbol();
    int getWeight();
    bool getIsUsable();

    void setName(std::string name);
    void setSymbol(char symbol);
};