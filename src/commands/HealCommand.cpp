//
// Created by pakamaka345 on 1/23/25.
//

#include "HealCommand.hpp"

#include <utility>
#include <entities/Entity.hpp>

HealCommand::HealCommand(float healAmount, std::shared_ptr<Entity> entity)
	: healAmount(healAmount), entity(std::move(entity))
{
}

void HealCommand::execute(GameState& gameState)
{
	if (entity) entity->heal(healAmount);
}
