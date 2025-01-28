//
// Created by pakamaka345 on 1/16/25.
//

#pragma once
#include "ThrowableItem.hpp"

class Grenade : public ThrowableItem {
private:
	float m_magicalDamage;
	float m_physicalDamage;

public:
	Grenade(float magicalDamage, float physicalDamage, int radius, int levelIndex);

	void use(Entity& target) override;

	std::string getSpecifications() override;
};


