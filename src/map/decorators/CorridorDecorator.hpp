//
// Created by pakamaka345 on 1/5/25.
//

#pragma once
#include "MapDecorator.hpp"


class CorridorDecorator : public MapDecorator {
public:
	explicit CorridorDecorator(int levelIndex);
	void decorate(Map& map) override;
};


