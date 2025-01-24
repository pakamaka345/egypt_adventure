//
// Created by pakamaka345 on 1/23/25.
//

#pragma once
#include <commands/Command.hpp>
#include <memory>

class Entity;

class HealCommand : public Command {
private:
	float healAmount;
	std::shared_ptr<Entity> entity;

public:
	HealCommand(float healAmount, std::shared_ptr<Entity> entity);
	void execute(GameState& gameState) override;
};
