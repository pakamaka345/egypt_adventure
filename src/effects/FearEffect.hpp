#pragma once
#include "effects/Effect.hpp"

class Entity;

class FearEffect : public Effect {
private:
    float fearPriority;

public:
    FearEffect(int duration, float fearPriority);
    ~FearEffect() override = default;

    void apply(Entity& target) override;
    void onTick(Entity& target) override;
    void remove(Entity& target) override;
};