#pragma once
#include <string>
#include "GameObject.hpp"

class Entity;

class Item : public GameObject
{
protected:
    std::string name;
    std::string description;

public:
    Item(std::string& name, std::string& description, int x, int y, char symbol);
    ~Item() override = default;

    virtual void use(Entity& target) = 0;

    std::string& getName();
    std::string& getDescription();

    [[nodiscard]] bool canBePlacedOn(TileType::TileType tileType) const override;
};