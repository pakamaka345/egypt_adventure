#include "effects/FearEffect.hpp"
#include "entities/Entity.hpp"
#include "modifiers/PriorityModifier.hpp"

FearEffect::FearEffect(int duration, float fearPriority)
    : fearPriority(fearPriority), Effect("fear effect", duration)
{
}

void FearEffect::apply(Entity &target) {
    auto modifier = std::make_shared<PriorityModifier>(fearPriority);
    target.addModifier(modifier);
    target.resetCooldown(target.getPriority());
    appliedModifier = modifier;
}

void FearEffect::onTick(Entity &target) {}

void FearEffect::remove(Entity &target) {
    target.removeModifier(appliedModifier);
}