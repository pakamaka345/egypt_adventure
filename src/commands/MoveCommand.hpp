//
// Created by pakamaka345 on 1/19/25.
//

#pragma once
#include <memory>
#include "Command.hpp"

class Entity;
struct Position;

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

class MoveCommand : public Command {
private:
	Direction direction;
	std::shared_ptr<Entity> entity;

public:
	MoveCommand(Direction direction, std::shared_ptr<Entity> entity);

	void execute(GameState& gameState) override;

private:
	[[nodiscard]] static Position getDirectionOffset(Direction direction) ;
};


