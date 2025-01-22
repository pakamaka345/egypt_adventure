//
// Created by pakamaka345 on 1/21/25.
//

#pragma once
#include <memory>
#include <vector>

class Entity;
class Position;
class Command;
class GameState;
class Map;
enum class Direction;

class AIComponent {
protected:
	std::weak_ptr<Entity> owner;
	bool hasSeenPlayer = false;

public:
	AIComponent() = default;
	explicit AIComponent(std::shared_ptr<Entity> owner);
	virtual ~AIComponent() = default;

	void setOwner(std::shared_ptr<Entity> owner);
	[[nodiscard]] std::shared_ptr<Entity> getOwner() const;

	std::shared_ptr<Command> makeDecision(GameState& gameState);

protected:
	bool canSeePlayer(const std::shared_ptr<Entity>& monster, const std::shared_ptr<Entity>& player, const std::shared_ptr<Map>& map) const;
	Direction findPath(const std::shared_ptr<Entity>& monster, const std::shared_ptr<Entity>& player, const std::shared_ptr<Map>& map) const;
	std::vector<Position> aStarSearch(const Position& start, const Position& goal, const std::shared_ptr<Map>& map) const;
	Direction convertPosToDirection(const Position& from, const Position& to) const;

	int heuristic(const Position& a, const Position& b) const;
	bool isDestination(const Position& src, const Position& dest) const;
};

