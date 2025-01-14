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
	Torch(int radius, int duration, const std::string &name, const std::string &description, int x, int y, char symbol);

	void use(Entity& target) override;

	int getRadius() const { return radius; }
	int decreaseDuration() { return duration--; }
};