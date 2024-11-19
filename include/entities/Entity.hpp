#pragma once
#include <string>
#include <vector>
#include <memory>
#include "GameObject.hpp"
#include "items/amulets/Amulet.hpp"

/**
 * \brief The Entity class represents a character in the game.
 */
class Entity : public GameObject
{
    /**
     * \brief A list of shared pointers to Amulet objects.
     */
    typedef std::vector<std::shared_ptr<Amulet>> AmuletList;

protected:
    std::string name;
    int health;
    float attackDamage;
    float defense;
    float priority;
    float dodgeChance;
    AmuletList activeAmulets;

public:
    Entity(const std::string& name, float attackDamage, int health, float defense,
           float priority, float dodgeChance, int x, int y, char symbol);

    bool isAlive() const;

    std::string& getName() const;




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
    virtual void takeDamage(float damage) = 0;

    /**
     * \brief Virtual method for healing.
     * \param amount The amount of health to be restored.
     */
    virtual void heal(int amount) = 0;

    /**
     * \brief Virtual method for applying an amulet effect.
     */
    virtual void applyAmuletEffect() = 0;

    // TODO - Add a method to move the entity
};

