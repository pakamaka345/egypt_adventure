//
// Created by pakamaka345 on 1/19/25.
//

#pragma once

class GameState;

class Command
{
public:
	virtual ~Command() = default;

	virtual void execute(GameState& gameState) = 0;
};