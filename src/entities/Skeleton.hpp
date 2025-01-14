#pragma once
#include "entities/Entity.hpp"

/**
 * \brief Skeleton is a second type of enemy in the game.
 * They have a higher attack range but also have same priority as the player.
 * Can be beaten by the player but also will not die without a fight.
 */
class Skeleton : public Entity
{
private:
    int resurrection;

public:
    Skeleton(const std::string& name, int attackRange, float physicalDamage, float magicalDamage,
             float health, float defense, float priority, float dodgeChance,
             int x, int y, char symbol);
    ~Skeleton() override = default;

    void attack(Entity& target) override;
    void takeDamage(float physicalDamage, float magicalDamage) override;
    void heal(float amount) override;
    void move(int dx, int dy) override;
    void update(Map& map) override;
    std::shared_ptr<Entity> clone() const override;
};