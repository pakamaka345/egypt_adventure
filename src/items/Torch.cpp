#include "items/Torch.hpp"

#include <entities/Character.hpp>

Torch::Torch(int radius, int duration,
             const std::string& name, const std::string& description, int x, int y, char symbol)
		: radius(radius), duration(duration)
		, Item(name, description, x, y, symbol)
{
}

void Torch::use(Entity& target)
{
	auto* character = dynamic_cast<Character*>(&target);
	if (character != nullptr) {
		character->setActiveTorch(std::make_unique<Torch>(*this));
	}
}

