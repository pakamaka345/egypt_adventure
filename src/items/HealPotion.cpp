#include "items/HealPotion.hpp"
#include "entities/Entity.hpp"
#include "effects/HealEffect.hpp"

HealPotion::HealPotion(float healAmount, int duration,
                       const std::string &name, const std::string &description, int x, int y, char symbol)
                       : healAmount(healAmount), duration(duration)
                       , Item(name, description, x, y, symbol)
{
}

void HealPotion::use(Entity &target) {
    target.applyEffects(std::make_shared<HealEffect>(duration, healAmount));
}