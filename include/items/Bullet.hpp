#pragma once
#include "items/Item.hpp"

class Bullet : public Item
{
protected:
    float physicalDamage;
    float magicalDamage;

public:
    explicit Bullet(float physicalDamage, float magicalDamage,
                    const std::string& name, const std::string& description, int x, int y, char symbol);
    ~Bullet() override = default;

    void use(Entity& target) override;

    void increasePhysicalDamage(float value);
    void increaseMagicalDamage(float value);

    void decreasePhysicalDamage(float value);
    void decreaseMagicalDamage(float value);

    float getPhysicalDamage() const { return physicalDamage; }
    float getMagicalDamage() const { return magicalDamage; }
};