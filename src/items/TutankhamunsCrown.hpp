//
// Created by pakamaka345 on 1/30/25.
//

#pragma once
#include "items/Item.hpp"

class TutankhamunsCrown : public Item {
public:
	explicit TutankhamunsCrown(int levelIndex);

	void use(Entity& target) override;

	std::string getSpecifications() override;
};

