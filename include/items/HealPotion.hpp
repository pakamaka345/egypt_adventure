#pragma once
#include "items/Item.hpp"
#include <string>

class Entity;

/**
 * \brief A class that represents a healing potion.
 * \param healAmount: The amount of health that the potion will heal per turn.
 * \param duration: The amount of turns that the potion will last.
 */
class HealPotion : public Item
{
private:
    float healAmount;
    int duration;

public:
    HealPotion(float healAmount, int duration,
               const std::string& name, const std::string& description, int x, int y, char symbol);
    ~HealPotion() override = default;

    void use(Entity& target) override;
};