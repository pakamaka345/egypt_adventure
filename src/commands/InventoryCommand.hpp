//
// Created by pakamaka345 on 1/27/25.
//

#pragma once
#include "Command.hpp"

class InventoryCommand : public Command {
public:
	void execute(GameState& gameState) override;
};


