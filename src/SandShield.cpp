#include "effects/SandShield.hpp"
#include "entities/Entity.hpp"
#include "entities/SandGolem.hpp"

SandShield::SandShield(int duration, float shieldAmount)
    : shieldAmount(shieldAmount), Effect("sand shield", duration)
{
}

void SandShield::apply(Entity &target) {
    auto sandGolem = dynamic_cast<SandGolem*>(&target);
    if (sandGolem) {
        sandGolem->setShieldHealth(shieldAmount);
    }
}

void SandShield::onTick(Entity &target) {}

void SandShield::remove(Entity &target) {
    auto sandGolem = dynamic_cast<SandGolem*>(&target);
    if (sandGolem) {
        sandGolem->setShieldHealth(0);
    }
}