//
// Created by pakamaka345 on 1/19/25.
//

#pragma once
#include <memory>

class Command;
class GameState;


class InputHandler {
private:
	GameState& gameState;

public:
	explicit InputHandler(GameState& gameState);

	[[nodiscard]] std::shared_ptr<Command> handleInput() const;

private:
	[[nodiscard]] char getInput() const;
};

