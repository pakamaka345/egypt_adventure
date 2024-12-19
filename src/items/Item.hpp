#pragma once
#include <string>
#include "GameObject.hpp"

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
    Item(const std::string& name, const std::string& description, int x, int y, char symbol);
    ~Item() override = default;

    virtual void use(Entity& target) = 0;
    virtual bool canBeUsedOnEnemies() const;
    virtual bool isConsumable() const;

    std::string& getName();
    std::string& getDescription();
};