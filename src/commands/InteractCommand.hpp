//
// Created by pakamaka345 on 1/27/25.
//

#pragma once
#include "Command.hpp"

class InteractCommand : public Command {
public:
	void execute(GameState& gameState) override;
};

