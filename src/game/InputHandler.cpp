//
// Created by pakamaka345 on 1/19/25.
//

#include "InputHandler.hpp"

#include <commands/MoveCommand.hpp>
#include <states/GameState.hpp>

#include "commands/ExitCommand.hpp"
#include "entities/Character.hpp"

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <cstdio>
#endif

InputHandler::InputHandler(GameState& gameState) : gameState(gameState)
{
}


std::shared_ptr<Command> InputHandler::handleInput() const
{
	char input = getInput();

	switch (input) {
		case 'w': return std::make_shared<MoveCommand>(Direction::UP, gameState.getPlayer());
		case 's': return std::make_shared<MoveCommand>(Direction::DOWN, gameState.getPlayer());
		case 'a': return std::make_shared<MoveCommand>(Direction::LEFT, gameState.getPlayer());
		case 'd': return std::make_shared<MoveCommand>(Direction::RIGHT, gameState.getPlayer());
		case 27: return std::make_shared<ExitCommand>();
		default: return nullptr;
	}
}

char InputHandler::getInput() const
{
	char input;
#ifdef _WIN32
	input = _getch();
#else
	struct termios oldt{}, newt{};
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	input = static_cast<char>(getchar());
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif

	return input;
}
