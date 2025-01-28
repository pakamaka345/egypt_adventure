#include "items/HealPotion.hpp"
#include "entities/Entity.hpp"
#include "effects/HealEffect.hpp"

HealPotion::HealPotion(float healAmount, int duration, int levelIndex)
                       : healAmount(healAmount), duration(duration)
                       , Item("heal potion", "An ancient decoction that can improve the well-being of the hero, and magically heal wounds.", 0, 0, levelIndex, 'p')
{
}

void HealPotion::use(Entity &target) {
    target.applyEffects(std::make_shared<HealEffect>(duration, healAmount));
}

std::string HealPotion::getSpecifications()
{
	std::string specs = "Heal amount: " + std::to_string(healAmount) + "\n";
	specs += "Duration: " + std::to_string(duration) + "\n";
	return specs;
}
