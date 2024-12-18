#pragma once
#include "effects/Effect.hpp"

class Entity;

/**
 * \brief An effect that provides a shield only for Sand Golems.
 */
class SandShield : public Effect
{
private:
    float shieldAmount;

public:
    SandShield(int duration, float shieldAmount);
    ~SandShield() override = default;

    void apply(Entity& target) override;
    void onTick(Entity& target) override;
    void remove(Entity& target) override;
};