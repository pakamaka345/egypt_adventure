//
// Created by pakamaka345 on 1/5/25.
//

#pragma once
#include "MapDecorator.hpp"

class StairsDecorator : public MapDecorator {
public:
	explicit StairsDecorator(int levelIndex);
	void decorate(Map& map) override;
};


