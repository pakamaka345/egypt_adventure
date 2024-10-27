#include "Player.hpp"
#include <iostream>

Player::Player(std::string name, int health, int strength, char symbol, int x, int y)
    : Entity(name, health, strength, symbol, x, y)
{
}

void Player::attack(Entity& target)
{
    //TODO implement
}

void Player::draw() const
{
    std::cout << getSymbol();
}

bool Player::canBePlacedOn(TileType::TileType tileType) const
{
    return tileType == TileType::TileType::FLOOR;
}