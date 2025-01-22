//
// Created by pakamaka345 on 1/21/25.
//

#include "AIComponent.hpp"
#include <utils/GameObject.hpp>
#include <commands/MoveCommand.hpp>
#include <dice/DiceRoll.hpp>
#include <entities/Entity.hpp>
#include <map/Map.hpp>
#include <tiles/Tile.hpp>
#include <entities/Character.hpp>
#include "states/GameState.hpp"
#include <set>

AIComponent::AIComponent(std::shared_ptr<Entity> owner) : owner(std::move(owner))
{
}

std::shared_ptr<Entity> AIComponent::getOwner() const
{
	if (owner.lock()) return owner.lock();
	throw std::runtime_error("Owner is expired");
}

void AIComponent::setOwner(std::shared_ptr<Entity> owner)
{
	this->owner = std::move(owner);
}

std::shared_ptr<Command> AIComponent::makeDecision(GameState& gameState)
{

	if (!getOwner()->isOnSameLevel(gameState.getPlayer())) return nullptr;

	DiceRoll gen;

	const auto& player = gameState.getPlayer();
	const auto& map = gameState.getCurrentLevel().getMap();

	if (canSeePlayer(getOwner(), player, map)) {
		hasSeenPlayer = true;
		auto path = findPath(getOwner(), player, map);
		if (path != Direction::NONE) {
			return std::make_shared<MoveCommand>(path, getOwner());
		}
	} else {
		if (hasSeenPlayer) {
			auto path = findPath(getOwner(), player, map);
			if (path != Direction::NONE) {
				return std::make_shared<MoveCommand>(path, getOwner());
			}
		} else {
			std::vector directions = {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT};
			return std::make_shared<MoveCommand>(directions[gen.randomNumber(0, 3)], getOwner());
		}
	}

	return nullptr;
}

bool AIComponent::canSeePlayer(const std::shared_ptr<Entity>& monster, const std::shared_ptr<Entity>& player, const std::shared_ptr<Map>& map) const
{

	auto monsterPos = monster->getPos();
	auto playerPos = player->getPos();

	auto delta = Position::abs(playerPos - monsterPos);
	int sx = (monsterPos.x < playerPos.x) ? 1 : -1;
	int sy = (monsterPos.y < playerPos.y) ? 1 : -1;
	int err = delta.x - delta.y;

	while (true) {
		if (!map->getTile(monsterPos.x, monsterPos.y)->isWalkable()) return false;

		if (monsterPos == playerPos) return true;

		const int e2 = err * 2;
		if (e2 > -delta.y) {
			err -= delta.y;
			monsterPos.x += sx;
		}
		if (e2 < delta.x) {
			err += delta.x;
			monsterPos.y += sy;
		}
	}
}

Direction AIComponent::findPath(const std::shared_ptr<Entity>& monster, const std::shared_ptr<Entity>& player, const std::shared_ptr<Map>& map) const
{

	if (canSeePlayer(monster, player, map)) {
		return convertPosToDirection(monster->getPos(), player->getPos());
	} else {
		auto path = aStarSearch(monster->getPos(), player->getPos(), map);
		if (path.empty()) return Direction::NONE;
		return convertPosToDirection(monster->getPos(), path[0]);
	}
}

std::vector<Position> AIComponent::aStarSearch(const Position& start, const Position& goal, const std::shared_ptr<Map>& map) const
{
	std::vector<Position> path;
	std::set<Position> openSet;
	std::set<Position> closedSet;

	std::unordered_map<Position, int> gCost;
	std::unordered_map<Position, int> hCost;
	std::unordered_map<Position, int> fCost;
	std::unordered_map<Position, Position> parent;

	gCost[start] = 0;
	hCost[start] = heuristic(start, goal);
	fCost[start] = gCost[start] + hCost[start];
	openSet.insert(start);

	while (!openSet.empty()) {
		auto current = *std::min_element(
			openSet.begin(),
			openSet.end(),
			[&](const Position& a, const Position& b)
			{
				return fCost[a] < fCost[b];
			});

		if (isDestination(current, goal)) {
			while (parent.find(current) != parent.end()) {
				path.push_back(current);
				current = parent[current];
			}
			std::reverse(path.begin(), path.end());
			return path;
		}

		openSet.erase(current);
		closedSet.insert(current);

		for (const auto& neighbor : map->getAdjacentTiles(current.x, current.y)) {
			if (closedSet.find(neighbor->getPos()) != closedSet.end() || !neighbor->isWalkable()) {
				continue;
			}

			int tentativeG = gCost[current] + 1;

			if (openSet.find(neighbor->getPos()) == openSet.end() || tentativeG < gCost[neighbor->getPos()]) {
				gCost[neighbor->getPos()] = tentativeG;
				hCost[neighbor->getPos()] = heuristic(neighbor->getPos(), goal);
				fCost[neighbor->getPos()] = gCost[neighbor->getPos()] + hCost[neighbor->getPos()];
				parent[neighbor->getPos()] = current;

				openSet.insert(neighbor->getPos());
			}
		}
	}

	return path;
}


Direction AIComponent::convertPosToDirection(const Position& from, const Position& to) const
{
	auto pos = to - from;
	if (pos.y == 0 && pos.x > 0) return Direction::RIGHT;
	if (pos.y == 0 && pos.x < 0) return Direction::LEFT;
	if (pos.x == 0 && pos.y > 0) return Direction::DOWN;
	if (pos.x == 0 && pos.y < 0) return Direction::UP;

	DiceRoll gen;
	if (pos.x > 0 && pos.y > 0) return gen.randomNumber(0, 1) ? Direction::RIGHT : Direction::DOWN;
	if (pos.x > 0 && pos.y < 0) return gen.randomNumber(0, 1) ? Direction::RIGHT : Direction::UP;
	if (pos.x < 0 && pos.y > 0) return gen.randomNumber(0, 1) ? Direction::LEFT : Direction::DOWN;
	if (pos.x < 0 && pos.y < 0) return gen.randomNumber(0, 1) ? Direction::LEFT : Direction::UP;

	return Direction::NONE;
}

int AIComponent::heuristic(const Position& a, const Position& b) const
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}

bool AIComponent::isDestination(const Position& src, const Position& dest) const
{
	return abs(src.x - dest.x) + abs(src.y - dest.y) <= 1;
}



