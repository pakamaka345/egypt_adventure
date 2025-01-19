#include "items/Torch.hpp"

#include <entities/Character.hpp>

Torch::Torch(int radius, int duration, int levelIndex)
		: radius(radius), duration(duration)
		, Item("torch", "Ancient torches were made by egyption a thousand years ago.", 0, 0, levelIndex, 't')
{
}

void Torch::use(Entity& target)
{
	auto* character = dynamic_cast<Character*>(&target);
	if (character != nullptr) {
		character->setActiveTorch(std::make_unique<Torch>(*this));
	}
}

