//
// Created by pakamaka345 on 1/19/25.
//

#pragma once
#include <memory>

class GameState;
class Command;

class GameController {
private:
	GameState& gameState;

public:
	explicit GameController(GameState& gameState);

	void executeCommand(const std::shared_ptr<Command>& command) const;

	void update() const;
};

