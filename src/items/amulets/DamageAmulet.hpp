//
// Created by pakamaka345 on 1/14/25.
//

#pragma once
#include "Amulet.hpp"

class PhysicalDamageModifier;
class MagicalDamageModifier;

class DamageAmulet : public Amulet {
private:
	float m_physicalDamage;
	float m_magicalDamage;

	std::shared_ptr<PhysicalDamageModifier> m_physicalDamageModifier;
	std::shared_ptr<MagicalDamageModifier> m_magicalDamageModifier;

public:
	DamageAmulet(float physicalDamage, float magicalDamage, int levelIndex);

	void applyAmuletEffect(Entity& target) override;
	void removeAmuletEffect(Entity& target) override;

	std::string getSpecifications() override;
};

