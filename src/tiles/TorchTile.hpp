//
// Created by pakamaka345 on 1/5/25.
//

#pragma once
#include "tiles/InteractTile.hpp"


class TorchTile : public InteractTile {
	int radius;
	bool isLit;

public:
	TorchTile(int radius, int x, int y, int z);

	void onInteract(GameState& gameState) override;

private:
	void forEachTileOnLine(int x0, int y0, int x1, int y1, const std::function<bool(int, int)>& callback);
};
