//
// Created by pakamaka345 on 1/25/25.
//

#pragma once
#include "Command.hpp"
#include <memory>

class Entity;

class ActivateSandShieldCommand : public Command {
private:
	std::shared_ptr<Entity> entity;

public:
	ActivateSandShieldCommand(std::shared_ptr<Entity> entity);

	void execute(GameState& gameState) override;
};


