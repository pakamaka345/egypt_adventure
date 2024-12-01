#pragma once
#include <memory>
#include <utility>
#include "entities/Entity.hpp"
#include "items/Item.hpp"

class Amulet : public Item {
public:
    Amulet(const std::string& name, const std::string& description, int x, int y, char symbol) : Item(name, description, x, y, symbol) {}
    ~Amulet() override = default;

    void use(Entity& target) override {
        applyEffect(target);
    }

    virtual void deactivate(Entity& target) = 0;

protected:
    virtual void applyEffect(Entity& target) = 0;
};