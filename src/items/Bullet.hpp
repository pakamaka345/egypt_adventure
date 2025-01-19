#pragma once
#include "items/Item.hpp"

class Entity;
class Character;
class Weapon;

/**
 * \brief Bullet class represents a bullet item that can be used by a weapon.
 * Can be parent class for different types of bullets.
 */
class Bullet : public Item
{
private:
    float physicalDamage;
    float magicalDamage;

public:
    explicit Bullet(float physicalDamage, float magicalDamage, int levelIndex);
    ~Bullet() override = default;

    void use(Entity& target) override;

    void increasePhysicalDamage(float value);
    void increaseMagicalDamage(float value);

    void decreasePhysicalDamage(float value);
    void decreaseMagicalDamage(float value);

    float getPhysicalDamage() const { return physicalDamage; }
    float getMagicalDamage() const { return magicalDamage; }
};