//
// Created by pakamaka345 on 1/25/25.
//

#include "ActivateSandShieldCommand.hpp"
#include <entities/SandGolem.hpp>

ActivateSandShieldCommand::ActivateSandShieldCommand(std::shared_ptr<Entity> entity)
	: entity(std::move(entity))
{
}

void ActivateSandShieldCommand::execute(GameState& gameState)
{
	if (const auto golem = std::dynamic_pointer_cast<SandGolem>(entity)) {
		golem->activateSandShield();
	}
}
