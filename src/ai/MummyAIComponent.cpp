//
// Created by pakamaka345 on 1/24/25.
//

#include "MummyAIComponent.hpp"
#include <entities/Mummy.hpp>
#include <entities/Character.hpp>
#include <states/GameState.hpp>
#include <dice/DiceRoll.hpp>
#include <commands/AttackCommand.hpp>
#include <commands/SummonMinionsCommand.hpp>

std::shared_ptr<Mummy> MummyAIComponent::getMummy() const
{
	return std::dynamic_pointer_cast<Mummy>(getOwner());
}

std::shared_ptr<Command> MummyAIComponent::makeDecision(GameState& gameState)
{
	DiceRoll gen;

	const auto& mummy = getMummy();
	const auto& player = gameState.getPlayer();
	const auto& map = gameState.getCurrentLevel().getMap();

	if (!mummy->isOnSameLevel(player)) {
		if (mummy->getHealth() < mummy->getMaxHealth()) return heal(mummy, gen);
		return movement(mummy, player->getPos(), map, gen);
	}

	if (mummy->isReady() && mummy->canAttack(*player)) {
		return attack(mummy, player, map, gen);
	}

	if (mummy->isReady() && mummy->getHealth() < mummy->getMaxHealth() / 2) {
		return heal(mummy, gen);
	}

	if (mummy->isReady() && !mummy->canAttack(*player)) {
		return movement(mummy, player->getPos(), map, gen);
	}

	return nullptr;
}

std::shared_ptr<Command> MummyAIComponent::attack(const std::shared_ptr<Entity>& monster, const std::shared_ptr<Entity>& player, const std::shared_ptr<Map>& map, DiceRoll gen)
{
	float chanceToSummon = static_cast<float>(gen.randomNumber(0, 100)) / 100.0f;

	if (chanceToSummon <= 0.1f && monster->getName() != "Mummy Minion") {
		return std::make_shared<SummonMinionsCommand>(monster);
	}

	if (static_cast<float>(gen.randomNumber(0, 100)) / 100.0f > player->getDodgeChance()) {
		if (canSeePlayer(monster, player->getPos(), map))
			return std::make_shared<AttackCommand>(monster, player);

		return nullptr;
	}

	monster->resetCooldown(monster->getPriority());
	return nullptr;
}


