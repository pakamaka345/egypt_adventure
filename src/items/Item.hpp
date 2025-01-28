#pragma once
#include <string>
#include "utils/GameObject.hpp"

class Entity;

/**
 * \brief Base class for all items in the game.
 */
class Item : public GameObject
{
protected:
    std::string name;
    std::string description;

public:
    Item(const std::string& name, const std::string& description, int x, int y, int z, char symbol);
    ~Item() override = default;

    virtual void use(Entity& target) = 0;
    [[nodiscard]] virtual bool canBeUsedOnEnemies() const;
    [[nodiscard]] virtual bool isConsumable() const;

    std::string& getName();
    std::string& getDescription();
    virtual std::string getSpecifications() = 0;
};