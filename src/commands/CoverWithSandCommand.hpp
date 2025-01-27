//
// Created by pakamaka345 on 1/25/25.
//

#pragma once
#include "Command.hpp"
#include <memory>

class Entity;

class CoverWithSandCommand : public Command {
private:
	std::shared_ptr<Entity> entity;

public:
	CoverWithSandCommand(std::shared_ptr<Entity> entity);

	void execute(GameState& gameState) override;
};

