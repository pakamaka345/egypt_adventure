//
// Created by pakamaka345 on 1/24/25.
//

#pragma once
#include "Command.hpp"
#include <memory>

class Entity;

class SummonMinionsCommand : public Command {
private:
	std::shared_ptr<Entity> entity;

public:
	SummonMinionsCommand(std::shared_ptr<Entity> entity);

	void execute(GameState& gameState) override;
};

