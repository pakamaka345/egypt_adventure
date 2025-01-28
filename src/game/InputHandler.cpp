//
// Created by pakamaka345 on 1/19/25.
//

#include "InputHandler.hpp"

#include <commands/MoveCommand.hpp>
#include <states/GameState.hpp>

#include "commands/AmuletsMenuCommand.hpp"
#include "commands/AttackCommand.hpp"
#include "commands/ExitCommand.hpp"
#include "commands/InteractCommand.hpp"
#include "commands/ReloadCommand.hpp"
#include "commands/InventoryCommand.hpp"
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


std::shared_ptr<Command> InputHandler::handleInput()
{
	char input = getInput();

	switch (input) {
		case 'w': return std::make_shared<MoveCommand>(Direction::UP, gameState.getPlayer());
		case 's': return std::make_shared<MoveCommand>(Direction::DOWN, gameState.getPlayer());
		case 'a': return std::make_shared<MoveCommand>(Direction::LEFT, gameState.getPlayer());
		case 'd': return std::make_shared<MoveCommand>(Direction::RIGHT, gameState.getPlayer());
		case 'e': return std::make_shared<InteractCommand>();
		case 'r': return std::make_shared<ReloadCommand>();
		case 'f': return attackCommand();
		case 'i': return std::make_shared<InventoryCommand>();
		case 'k': return std::make_shared<AmuletsMenuCommand>();
		case 27: return std::make_shared<ExitCommand>();
		default: return nullptr;
	}
}

std::shared_ptr<Command> InputHandler::attackCommand()
{
	std::shared_ptr<Entity> bestTarget = nullptr;
	float minDistance = std::numeric_limits<float>::max();
	const auto& player = gameState.getPlayer();
	const double halfFovAngle = player->getFov() / 2;
	const double facingAngle = player->calculateFacingAngle();

	for (auto& entity : gameState.getCurrentLevel().getEntities()) {
		if (!entity->isAlive() || entity == player) continue;

		int distance = player->distanceTo(*entity);
		if (distance > player->getAttackRange()) continue;

		double dx = entity->getX() - player->getX();
		double dy = entity->getY() - player->getY();
		double angleToTarget = atan2(dy, dx) * 180 / M_PI;
		if (angleToTarget < 0) angleToTarget += 360;

		double angleDiff = std::fabs(std::remainder(angleToTarget - facingAngle, 360.0));
		if (angleDiff > halfFovAngle) continue;

		if (distance < minDistance) {
			if (player->canAttack(*entity)) {
				minDistance = distance;
				bestTarget = entity;
			}
		}
	}

	if (bestTarget) {
		return std::make_shared<AttackCommand>(player, bestTarget);
	}
	return nullptr;
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
