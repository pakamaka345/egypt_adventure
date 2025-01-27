//
// Created by pakamaka345 on 1/5/25.
//

#pragma once
#include <string>
#include <utility>
#include "tiles/Tile.hpp"

class GameState;

class InteractTile : public Tile {
private:
	std::string name;
public:
	InteractTile(std::string  name, const TileType::Type type, const int x, const int y, const int z, const char symbol)
		: Tile(type, x, y, z, symbol), name(std::move(name)) {}

	virtual void onInteract(GameState& gameState) = 0;

	[[nodiscard]] std::string getName() const { return name; }
	void setName(std::string name) { this->name = std::move(name); }
};



