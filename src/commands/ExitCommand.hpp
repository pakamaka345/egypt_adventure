//
// Created by pakamaka345 on 1/19/25.
//

#pragma once
#include "Command.hpp"

class ExitCommand : public Command {
public:
	void execute(GameState& gameState) override;
};


