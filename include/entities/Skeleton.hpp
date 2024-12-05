#pragma once
#include "entities/Entity.hpp"

// TODO: Maybe add methods to do smth after death (like a resurrection)
/**
 * \brief Skeleton is a second type of enemy in the game.
 * They have a higher attack range but also have same priority as the player.
 * Can be beaten by the player but also will not die without a fight.
 */
class Skeleton : public Entity
{
public:
    Skeleton(const std::string& name, int attackRange, float attackDamage,
             float health, float defense, float priority, float dodgeChance,
             int x, int y, char symbol);
    ~Skeleton() override = default;

    void attack(Entity& target) override;
    void takeDamage(float physicalDamage, float magicalDamage) override;
    void heal(float amount) override;
    void move(int dx, int dy) override;
    void update() override;
    std::shared_ptr<Entity> clone() const override;
};