#pragma once
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>
#include <random>
#include <stdexcept>
#include "GameObject.hpp"
#include "items/amulets/Amulet.hpp"

/**
 * \brief The Entity class represents a game object that can be attacked and can attack other entities.
 */
class Entity : public GameObject
{
    /**
     * \brief A list of shared pointers to Amulet objects.
     */
    typedef std::vector<std::shared_ptr<Amulet>> AmuletList;

protected:
    std::string name;
    float health;
    float maxHealth;
    int attackRange;
    float attackDamage;
    float defense;
    float priority;
    int cooldown;
    float dodgeChance;
    AmuletList activeAmulets;

public:
    Entity(std::string& name, int attackRange, float attackDamage, float health, float defense,
           float priority, float dodgeChance, int x, int y, char symbol);
    ~Entity() override = default;

    void addAmulet(const std::shared_ptr<Amulet>& amulet);
    void removeAmulet(const std::shared_ptr<Amulet>& amulet);
    bool canBePlacedOn(TileType::TileType tileType) const override;

    bool isAlive() const;

    bool canAttack(Entity& target) const;

    bool isReady() { return cooldown <= 0; }
    void reduceCooldown() { cooldown = std::max(0, cooldown - 1); }
    void resetCooldown(int turns) { cooldown = turns; }

    std::string& getName();
    float getHealth() const;
    float getMaxHealth() const;
    int getAttackRange() const;
    float getAttackDamage() const;
    float getDefense() const;
    float getPriority() const;
    int getCooldown() const;
    float getDodgeChance() const;


public:
    /**
     * \brief Virtual method for attacking another entity.
     * \param target The Entity which will be attacked.
     */
    virtual void attack(Entity& target) = 0;

    /**
     * \brief Virtual method for taking damage.
     * \param damage The amount of damage to be taken.
     */
    virtual void takeDamage(float physicalDamage, float magicalDamage) = 0;

    /**
     * \brief Virtual method for healing.
     * \param amount The amount of health to be restored.
     */
    virtual void heal(float amount) = 0;

    // TODO - Add a method to move the entity
    virtual void move(int x, int y) = 0;
};

