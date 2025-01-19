//
// Created by pakamaka345 on 1/5/25.
//

#pragma once

class Map;

class MapDecorator
{
protected:
	int levelIndex;

public:
	explicit MapDecorator(const int levelIndex) : levelIndex(levelIndex) {}

	virtual void decorate(Map& map) = 0;
	virtual ~MapDecorator() = default;
};