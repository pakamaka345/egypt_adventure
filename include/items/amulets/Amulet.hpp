#pragma once
#include <memory>
#include <utility>

class Item;

/**
 * \brief An amulet is a type of item that can be equipped and give permanent effects during amulet is equipped.
 * Specific amulets will inherit from this class and implement their own effects.
 */
class Amulet : public Item, public std::enable_shared_from_this<Amulet> {
public:
    Amulet(const std::string& name, const std::string& description, int x, int y, char symbol) : Item(name, description, x, y, symbol) {}
    ~Amulet() override = default;

    void use(Entity& target) override {
        target.addAmulet(shared_from_this());
    }

    virtual void applyAmuletEffect(Entity& target) = 0;
    virtual void removeAmuletEffect(Entity& target) = 0;
};