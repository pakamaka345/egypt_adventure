#pragma once
#include "entities/Entity.hpp"


/**
 * \brief Phantom can be defeated by the player but with a lot of effort.
 * One of the reasons is that pharaon's phantoms take only 10% of the physical damage and player
 * in the start only has physical damage. But after the player gets the amulets that give him magical damage
 * it will be easier to defeat the phantoms. Other reason is that phantoms have chance to give fear effect to the player.
 */
class Phantom : public Entity {
public:
    Phantom(const std::string& name, int attackRange, float physicalDamage, float magicalDamage,
          float health, float defense, float priority, float dodgeChance,
          int x, int y, int z, char symbol);
    ~Phantom() override = default;

    void attack(Entity& target) override;
    void takeDamage(float physicalDamage, float magicalDamage) override;
    void heal(float amount) override;
    void move(int dx, int dy) override;
    void update(GameState& gameState) override;
	void onDeath(GameState& gameState) override;
    std::shared_ptr<Entity> clone() const override;
};