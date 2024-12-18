#pragma once
#include "effects/Effect.hpp"

class Entity;

class GroupAttackBonus : public Effect {
private:
    float bonusDamageMultiplier;

public:
    GroupAttackBonus(int duration, float multiplier);
    ~GroupAttackBonus() override = default;

    void apply(Entity& target) override;
    void onTick(Entity& target) override;
    void remove(Entity& target) override;
};