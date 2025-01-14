#pragma once
#include <memory>
#include "effects/Effect.hpp"

class Entity;
class PriorityModifier;

class FearEffect : public Effect {
private:
    float fearPriority;
    std::shared_ptr<PriorityModifier> appliedModifier;

public:
    FearEffect(int duration, float fearPriority);
    ~FearEffect() override = default;

    void apply(Entity& target) override;
    void onTick(Entity& target) override;
    void remove(Entity& target) override;
};