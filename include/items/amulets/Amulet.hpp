#pragma once
#include <memory>
#include <utility>
#include "items/Item.hpp"

class Amulet : public Item {
public:
    Amulet(std::string name, std::string description, int x, int y, char symbol) : Item(name, description, x, y, symbol) {}
    ~Amulet() override = default;

    void use(std::shared_ptr<Entity> target) override {
        applyEffect(target);
    }


protected:
    virtual void applyEffect(std::shared_ptr<Entity> target) = 0;
};