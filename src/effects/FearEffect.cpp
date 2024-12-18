#include "effects/FearEffect.hpp"
#include "entities/Entity.hpp"

FearEffect::FearEffect(int duration, float fearPriority)
    : fearPriority(fearPriority), Effect("fear effect", duration)
{
}

void FearEffect::apply(Entity &target) {
    float currentPriority = target.getPriority();
    target.setPriority(currentPriority + fearPriority);
    target.resetCooldown(target.getPriority());
}

void FearEffect::onTick(Entity &target) {}

void FearEffect::remove(Entity &target) {
    float currentPriority = target.getPriority();
    target.setPriority(currentPriority - fearPriority);
}