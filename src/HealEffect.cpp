#include "effects/HealEffect.hpp"
#include "entities/Entity.hpp"

HealEffect::HealEffect(int duration, float healAmount)
    : healAmount(healAmount), Effect("Heal effect", duration)
{
}

void HealEffect::apply(Entity &target) {
    // Apply the heal effect to the target entity
}

void HealEffect::onTick(Entity &target) {
    if (!isExpired()) {
        target.heal(healAmount);
    }
}

void HealEffect::remove(Entity &target) {
    // Remove the heal effect from the target entity
}