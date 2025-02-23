#pragma once
#include "entities/Entity.hpp"


/**
 * \brief Now sand golem will represent a big man who is just has a low of health and other stats
 * But i plan change it and make it more interesting
 * but in any case it will be a strong enemy for the start player.
 */
class SandGolem : public Entity
{
private:
    float maxShieldHealth;
    float shieldHealth;

	int sandTimer = 0;

public:
    SandGolem(const std::string& name, int attackRange, float physicalDamage, float magicalDamage,
          float health, float defense, float priority, float dodgeChance,
          int x, int y, int z, char symbol);
    ~SandGolem() override = default;

    void attack(Entity& target) override;
    void takeDamage(float physicalDamage, float magicalDamage) override;
    void heal(float amount) override;
    void move(int dx, int dy) override;
    void update(GameState& gameState) override;
	void onDeath(GameState& gameState) override;
    std::shared_ptr<Entity> clone() const override;

    void activateSandShield();
    void coverWithSand(Map& map, int radius);
    void healOnSand(Map& map);

    void setShieldHealth(float shieldHealth);
    float getShieldHealth() const;
	float getShieldMaxHealth() const;
};