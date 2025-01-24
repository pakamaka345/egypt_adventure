//
// Created by pakamaka345 on 1/21/25.
//

#pragma once
#include <memory>
#include <vector>
#include "utils/GameObject.hpp"

class Entity;
class Command;
class GameState;
class Map;
enum class Direction;
class DiceRoll;

class AIComponent {
protected:
	std::weak_ptr<Entity> owner;
	bool hasSeenPlayer = false;
	Position lastPlayerPosition;

public:
	AIComponent() = default;
	explicit AIComponent(const std::shared_ptr<Entity>& owner);
	virtual ~AIComponent() = default;

	void setOwner(const std::shared_ptr<Entity>& owner);
	[[nodiscard]] std::shared_ptr<Entity> getOwner() const;

	virtual std::shared_ptr<Command> makeDecision(GameState& gameState);

protected:
	virtual std::shared_ptr<Command> movement(const std::shared_ptr<Entity>& monster, const Position& playerPosition, const std::shared_ptr<Map>& map, DiceRoll gen);
	virtual std::shared_ptr<Command> attack(const std::shared_ptr<Entity>& monster, const std::shared_ptr<Entity>& player, const std::shared_ptr<Map>& map, DiceRoll gen);
	virtual std::shared_ptr<Command> heal(const std::shared_ptr<Entity>& monster, DiceRoll gen);

	bool canSeePlayer(const std::shared_ptr<Entity>& monster, const Position& playerPosition, const std::shared_ptr<Map>& map) const;
	Direction findPath(const std::shared_ptr<Entity>& monster, const Position& playerPosition, const std::shared_ptr<Map>& map) const;
	std::vector<Position> aStarSearch(const Position& start, const Position& goal, const std::shared_ptr<Map>& map) const;
	Direction convertPosToDirection(const Position& from, const Position& to) const;

	int heuristic(const Position& a, const Position& b) const;
	bool isDestination(const Position& src, const Position& dest) const;
};

