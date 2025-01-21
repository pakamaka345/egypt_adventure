#pragma once
#include "entities/Entity.hpp"

/**
 * \brief Scarab a simple enemy that appears in the game
 * One scarab can not make a lot of damage but they can be dangerous in groups
 * They have a low health, defense, dodge chance and attack damage but they have a low priority that makes them attack faster
 */
class Scarab : public Entity
{
private:
    float groupAttackBonus;
public:
    Scarab(const std::string& name, int attackRange, float physicalDamage, float magicalDamage,
           float health, float defense, float priority, float dodgeChance,
           int x, int y, int z, char symbol);
    ~Scarab() override = default;

    void attack(Entity& target) override;
    void takeDamage(float physicalDamage, float magicalDamage) override;
    void heal(float amount) override;
    void move(int dx, int dy) override;
    void update(GameState& gameState) override;
    std::shared_ptr<Entity> clone() const override;

    void setGroupAttackBonus(float bonus);
    float getGroupAttackBonus() const;

private:
	void findNearestScarabs(const Map& map);
};