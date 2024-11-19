#pragma once
#include <string>
#include <memory>
#include "GameObject.hpp"
#include "entities/Entity.hpp"

class Item : public GameObject
{
protected:
    std::string name;
    std::string description;

public:
    Item(std::string& name, std::string& description, int x, int y, char symbol);
    ~Item() override = default;

    virtual void use(std::shared_ptr<Entity> target) = 0;

    [[nodiscard]] std::string& getName();
    [[nodiscard]] std::string& getDescription();

    [[nodiscard]] bool canBePlacedOn(TileType::TileType tileType) const override;
};