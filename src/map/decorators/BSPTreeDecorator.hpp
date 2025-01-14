//
// Created by pakamaka345 on 1/5/25.
//

#pragma once
#include "MapDecorator.hpp"

class BSPTreeDecorator : public MapDecorator {
	int minLeafSize, maxLeafSize;

public:
	BSPTreeDecorator(int minLeafSize, int maxLeafSize);

	void decorate(Map& map) override;
};


