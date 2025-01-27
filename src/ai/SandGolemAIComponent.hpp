//
// Created by pakamaka345 on 1/25/25.
//

#pragma once
#include "ai/AIComponent.hpp"

class SandGolem;

class SandGolemAIComponent : public AIComponent {
protected:
	bool isSpecialActionActivated = false;
	bool isShieldActivated = false;

public:
	[[nodiscard]] std::shared_ptr<SandGolem> getGolem() const;

	std::shared_ptr<Command> makeDecision(GameState& gameState) override;

protected:
	std::shared_ptr<Command> movement(const std::shared_ptr<Entity>& monster, const Position& playerPosition, const std::shared_ptr<Map>& map, DiceRoll gen) override;

	std::vector<Position> getTilesWithSand(const std::shared_ptr<Map>& map) const;
};
