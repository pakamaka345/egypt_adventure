//
// Created by pakamaka345 on 1/5/25.
//

#include "TorchTile.hpp"
#include <states/GameState.hpp>
#include <map/Map.hpp>

TorchTile::TorchTile(int radius, int x, int y, int z)
	: InteractTile("Torch", TileType::TORCH, x, y, z, '!'), radius(radius), isLit(false)
{
}

void TorchTile::onInteract(GameState& gameState)
{
	const auto& map = gameState.getCurrentLevel().getMap();
	const int torchX = getX();
	const int torchY = getY();

	for (int dx = -radius; dx <= radius; ++dx) {
		for (int dy = -radius; dy <= radius; ++dy) {
			int targetX = torchX + dx;
			int targetY = torchY + dy;

			if (!map->isInsideMap(targetX, targetY)) continue;

			if (dx * dx + dy * dy > radius * radius) continue;

			bool blocked = false;
			forEachTileOnLine(torchX, torchY, targetX, targetY, [&](int x, int y)
			{
				if (blocked) return false;

				if (map->getTile(x, y)->getTileType() == TileType::WALL) {
					map->setLightMap(x, y, LightType::STATIC);
					blocked = true;
					return false;
				}

				map->setLightMap(x, y, LightType::STATIC);
				return true;
			});
		}
	}
}

void TorchTile::forEachTileOnLine(int x0, int y0, int x1, int y1, const std::function<bool(int, int)>& callback)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx - dy;

	while (true) {
		if (!callback(x0, y0)) break;

		if (x0 == x1 && y0 == y1) break;

		int e2 = err * 2;
		if (e2 > -dy) {
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y0 += sy;
		}
	}
}

