//
// Created by pakamaka345 on 1/13/25.
//

#pragma once
#include "Item.hpp"

class Torch : public Item
{
private:
	int radius;
	int duration;

public:
	Torch(int radius, int duration, int levelIndex);

	void use(Entity& target) override;

	int getRadius() const { return radius; }
	int decreaseDuration() { return duration--; }
};