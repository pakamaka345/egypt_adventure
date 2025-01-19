//
// Created by pakamaka345 on 1/19/25.
//

#pragma once
#include <memory>
#include "Command.hpp"

class Entity;


class MoveCommand : public Command {
private:
	int dx;
	int dy;
	std::shared_ptr<Entity> entity;

public:
	MoveCommand(int dx, int dy, std::shared_ptr<Entity> entity);

	void execute(GameState& gameState) override;
};


