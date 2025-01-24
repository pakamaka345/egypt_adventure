//
// Created by pakamaka345 on 1/23/25.
//

#pragma once
#include <memory>
#include "Command.hpp"

class Entity;

class AttackCommand : public Command {
private:
	std::shared_ptr<Entity> attacker;
	std::shared_ptr<Entity> target;

public:
	AttackCommand(std::shared_ptr<Entity> attacker, std::shared_ptr<Entity> target);

	void execute(GameState& gameState) override;
};

