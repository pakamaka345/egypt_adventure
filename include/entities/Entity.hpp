#pragma once
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>
#include <random>
#include <stdexcept>
#include "GameObject.hpp"
#include "effects/EffectManager.hpp"

class Item;
class Amulet;
class Effect;

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
    float cooldown;
    float dodgeChance;
    AmuletList activeAmulets;
    EffectManager effectManager;

public:
    Entity(const std::string& name, int attackRange, float attackDamage, float health, float defense,
           float priority, float dodgeChance, int x, int y, char symbol);
    ~Entity() override = default;

    void addAmulet(const std::shared_ptr<Amulet>& amulet);
    void removeAmulet(const std::shared_ptr<Amulet>& amulet);


    bool canBePlacedOn(TileType::Type tileType) const override;
    bool isAlive() const;
    bool canAttack(Entity& target) const;

    void applyEffects(const std::shared_ptr<Effect>& effect);
    void updateEffects();
    void removeEffects();

    bool isReady() { return cooldown <= 0; }
    void reduceCooldown() { cooldown = std::max(0.0f, cooldown - 1); }
    void resetCooldown(float turn) { cooldown = turn; }

    std::string& getName();
    float getHealth() const;
    float getMaxHealth() const;
    int getAttackRange() const;
    float getAttackDamage() const;
    float getDefense() const;
    float getPriority() const;
    float getCooldown() const;
    float getDodgeChance() const;
    AmuletList& getActiveAmulets();
    EffectManager& getEffectManager();

    void setHealth(float health);
    void setMaxHealth(float maxHealth);
    void setAttackRange(int attackRange);
    void setAttackDamage(float attackDamage);
    void setDefense(float defense);
    void setPriority(float priority);
    void setCooldown(float cooldown);
    void setDodgeChance(float dodgeChance);

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
    virtual void move(int dx, int dy) = 0;
};

