#pragma once
#include "items/Item.hpp"

class ThrowableItem : public Item {
private:
    int radius;

public:
    ThrowableItem(int radius, const std::string& name, const std::string& description, int x, int y, int z, char symbol);
    ~ThrowableItem() override = default;

    bool canBeUsedOnEnemies() const override;

    int getRadius() const { return radius; }
    void setRadius(int radius) { this->radius = radius; }
};