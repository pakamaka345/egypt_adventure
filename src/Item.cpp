#include "Item.hpp"

Item::Item(std::string name, int weight, bool isUsable, char symbol)
    : name(name), weight(weight), isUsable(isUsable), symbol(symbol)
{
}

std::string Item::getName()
{
    return name;
}   

char Item::getSymbol()
{
    return symbol;
}

int Item::getWeight()
{
    return weight;
}

bool Item::getIsUsable()
{
    return isUsable;
}

void Item::setName(std::string name)
{
    this->name = name;
}

void Item::setSymbol(char symbol)
{
    this->symbol = symbol;
}

