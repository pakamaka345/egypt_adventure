//
// Created by pakamaka345 on 1/24/25.
//

#pragma once
#include "ai/AIComponent.hpp"

class Mummy;

class MummyAIComponent : public AIComponent {
public:
	[[nodiscard]] std::shared_ptr<Mummy> getMummy() const;

	std::shared_ptr<Command> makeDecision(GameState& gameState) override;

protected:
	std::shared_ptr<Command> attack(const std::shared_ptr<Entity>& monster, const std::shared_ptr<Entity>& player, const std::shared_ptr<Map>& map, DiceRoll gen) override;
};

