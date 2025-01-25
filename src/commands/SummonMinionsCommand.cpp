//
// Created by pakamaka345 on 1/24/25.
//

#include "SummonMinionsCommand.hpp"

#include <entities/Mummy.hpp>

SummonMinionsCommand::SummonMinionsCommand(std::shared_ptr<Entity> entity)
	: entity(std::move(entity))
{
}

void SummonMinionsCommand::execute(GameState& gameState)
{
	if (const auto mummy = std::dynamic_pointer_cast<Mummy>(entity)) {
		mummy->summonMinions(gameState);
	}
}
