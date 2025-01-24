//
// Created by pakamaka345 on 1/23/25.
//

#pragma once
#include "Command.hpp"

class ReloadCommand : public Command {
public:
	void execute(GameState& gameState) override;
};

