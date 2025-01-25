#pragma once
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>
#include <random>
#include <stdexcept>
#include "utils/GameObject.hpp"
#include "effects/EffectManager.hpp"

class Item;
class Amulet;
class Effect;
class Modifier;
class GameState;
class Map;
class AIComponent;
class DiceRoll;
class LevelState;

/**
 * \brief The Entity class represents a game object that can be attacked and can attack other entities.
 */
class Entity : public GameObject
{
    /**
     * \brief A list of shared pointers to Amulet objects.
     */
    typedef std::vector<std::shared_ptr<Amulet>> AmuletList;

    /**
     * \brief A list of modifiers that affect the entity.
     */
    typedef std::vector<std::shared_ptr<Modifier>> ModifierList;

protected:
    std::string name;
    float health;
    float maxHealth; // with modifiers
    int attackRange;
    float physicalDamage; // with modifiers
    float magicalDamage; // with modifiers
    float defense; // with modifiers
    float priority; // with modifiers
    float cooldown;
    float dodgeChance; // with modifiers
    AmuletList activeAmulets;
    ModifierList activeModifiers;
    EffectManager effectManager;
    std::shared_ptr<AIComponent> aiComponent;

public:
    Entity(std::string  name, int attackRange, float physicalDamage, float magicalDamage, float health, float defense,
           float priority, float dodgeChance, int x, int y, int z, char symbol);

    ~Entity() override = default;

    void addAmulet(const std::shared_ptr<Amulet>& amulet);
    void removeAmulet(const std::shared_ptr<Amulet>& amulet);

    void addModifier(const std::shared_ptr<Modifier>& modifier);
    void removeModifier(const std::shared_ptr<Modifier>& modifier);

    bool isAlive() const;
    bool canAttack(Entity& target) const;

    void applyEffects(const std::shared_ptr<Effect>& effect);
    void updateEffects();
    void removeEffects();

    bool isOnSameLevel(const std::shared_ptr<Entity>& other) const;

    bool isReady() const { return cooldown <= 0; }
    void reduceCooldown() { cooldown = std::max(0.0f, cooldown - 1); }
    void resetCooldown(const float turn) { cooldown = turn; }

    /**
     * \brief Returns the distance to another entity.
     * \param target The entity to which the distance is calculated.
     * \return The distance to the target entity.
     */
    int distanceTo(Entity& target) const;

    std::string& getName();
    float getHealth() const;
    float getMaxHealth() const;
    int getAttackRange() const;
    virtual float getPhysicalDamage() const;
    virtual float getMagicalDamage() const;
    float getDefense() const;
    float getPriority() const;
    float getCooldown() const;
    float getDodgeChance() const;
    AmuletList& getActiveAmulets();
    EffectManager& getEffectManager();
    ModifierList& getActiveModifiers();
    std::shared_ptr<AIComponent> getAIComponent() const;

    void setHealth(float health);
    void setMaxHealth(float maxHealth);
    void setAttackRange(int attackRange);
    void setPhysicalDamage(float physicalDamage);
    void setMagicalDamage(float magicalDamage);
    void setDefense(float defense);
    void setPriority(float priority);
    void setCooldown(float cooldown);
    void setDodgeChance(float dodgeChance);
    void setAIComponent(const std::shared_ptr<AIComponent>& aiComponent);

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

    virtual void move(int dx, int dy);

    /**
     * \brief Virtual method for updating the entity.
     */
    virtual void update(GameState& gameState);

    /**
     * \brief Virtual method which update map after entity death
     */
    virtual void onDeath(GameState& gameState);

    virtual std::shared_ptr<Entity> clone() const = 0;

protected:
    void chanceToDropAmulets(int chance, DiceRoll gen, const std::shared_ptr<LevelState>& level, int gameLevel);
    void chanceToDropGrenades(int chance, DiceRoll gen, const std::shared_ptr<LevelState>& level, int gameLevel);
    void chanceToDropPotions(int chance, DiceRoll gen, const std::shared_ptr<LevelState>& level, int gameLevel);
};

