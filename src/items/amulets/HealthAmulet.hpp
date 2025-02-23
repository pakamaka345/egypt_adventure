//
// Created by pakamaka345 on 1/15/25.
//

#pragma once
#include "Amulet.hpp"

class HealthModifier;

class HealthAmulet : public Amulet {
private:
	float m_maxHeath;

	std::shared_ptr<HealthModifier> m_healthModifier;

public:
	HealthAmulet(float maxHealth, int levelIndex);

	void applyAmuletEffect(Entity& target) override;
	void removeAmuletEffect(Entity& target) override;

	std::string getSpecifications() override;
};


