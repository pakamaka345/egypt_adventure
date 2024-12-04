#pragma once
#include "effects/Effect.hpp"

class Entity;

/**
 * \brief An effect that heals the target entity by a certain amount every tick.
 */
class HealEffect : public Effect
{
private:
    float healAmount;

public:
    HealEffect(int duration, float healAmount);
    ~HealEffect() override = default;

    void apply(Entity& target) override;
    void onTick(Entity& target) override;
    void remove(Entity& target) override;
};