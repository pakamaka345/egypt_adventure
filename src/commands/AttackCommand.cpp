//
// Created by pakamaka345 on 1/23/25.
//

#include "AttackCommand.hpp"

#include <utility>
#include <entities/Entity.hpp>

AttackCommand::AttackCommand(std::shared_ptr<Entity> attacker, std::shared_ptr<Entity> target)
: attacker(std::move(attacker)), target(std::move(target))
{
}


void AttackCommand::execute(GameState& gameState)
{
	if (attacker && target) {
		attacker->attack(*target);
	}
}
