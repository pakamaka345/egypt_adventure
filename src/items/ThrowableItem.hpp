#pragma once
#include "items/Item.hpp"

class ThrowableItem : Item{
private:
    int radius;

public:
    ThrowableItem(int radius, const std::string& name, const std::string& description, int x, int y, char symbol);
    ~ThrowableItem() override = default;

    bool canBeUsedOnEnemies() const override;
};