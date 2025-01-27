//
// Created by pakamaka345 on 1/25/25.
//

#include "CoverWithSandCommand.hpp"
#include <states/GameState.hpp>
#include "entities/SandGolem.hpp"


CoverWithSandCommand::CoverWithSandCommand(std::shared_ptr<Entity> entity)
	: entity(std::move(entity))
{
}

void CoverWithSandCommand::execute(GameState& gameState)
{
	if (const auto golem = std::dynamic_pointer_cast<SandGolem>(entity))
	{
		golem->coverWithSand(*gameState.getLevels()[golem->getZ()]->getMap(), 5);
	}
}
