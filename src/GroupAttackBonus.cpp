#include "effects/GroupAttackBonus.hpp"
#include "entities/Entity.hpp"
#include "entities/Scarab.hpp"

GroupAttackBonus::GroupAttackBonus(int duration, float multiplier)
    : bonusDamageMultiplier(multiplier), Effect("group attack bonus", duration)
{
}

void GroupAttackBonus::apply(Entity &target) {
    auto scarab = dynamic_cast<Scarab*>(&target);
    if (scarab) {
        auto bonus = scarab->getGroupAttackBonus();
        scarab->setGroupAttackBonus(std::min(2.0f, bonus + bonusDamageMultiplier));
    }
}

void GroupAttackBonus::onTick(Entity &target) {}

void GroupAttackBonus::remove(Entity &target) {
    auto scarab = dynamic_cast<Scarab*>(&target);
    if (scarab) {
        auto bonus = scarab->getGroupAttackBonus();
        scarab->setGroupAttackBonus(std::max(1.0f, bonus - bonusDamageMultiplier));
    }
}