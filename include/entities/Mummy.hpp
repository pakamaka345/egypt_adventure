#pragma once
#include "entities/Entity.hpp"

/**
 * \brief Mummy is a the most familiar enemy to the player.
 * It has a worse priority than the player, but health and attack damage a bit better.
 * Now it is a real deal to player to fight with mummy.
 * Expected that player and mummy will have 50% chance to win.
 */
class Mummy : public Entity
{
public:
    Mummy(const std::string& name, int attackRange, float attackDamage,
          float health, float defense, float priority, float dodgeChance,
          int x, int y, char symbol);
    ~Mummy() override = default;

    void attack(Entity& target) override;
    void takeDamage(float physicalDamage, float magicalDamage) override;
    void heal(float amount) override;
    void move(int dx, int dy) override;
    void update() override;
    std::shared_ptr<Entity> clone() const override;

private:
    void regenerate();
};