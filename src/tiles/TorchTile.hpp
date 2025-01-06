//
// Created by pakamaka345 on 1/5/25.
//

#pragma once
#include "tiles/InteractTile.hpp"


class TorchTile : public InteractTile {
	int radius;
	bool isLit;

public:
	TorchTile(int radius, int x, int y);

	void onInteract() override;
};
