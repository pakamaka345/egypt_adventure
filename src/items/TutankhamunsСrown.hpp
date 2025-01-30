//
// Created by pakamaka345 on 1/30/25.
//

#pragma once
#include "items/Item.hpp"

class TutankhamunsСrown : public Item {
public:
	explicit TutankhamunsСrown(int levelIndex);

	void use(Entity& target) override;

	std::string getSpecifications() override;
};

