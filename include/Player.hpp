#pragma once
#include "Entity.hpp"

class Player : public Entity
{
public: 
    Player(std::string name, int health, int strength, char symbol, int x, int y);
    virtual ~Player() = default;

    void attack(Entity& target) override;
    void draw() const override;

    virtual bool canBePlacedOn(TileType::TileType tileType) const override;

private:

};