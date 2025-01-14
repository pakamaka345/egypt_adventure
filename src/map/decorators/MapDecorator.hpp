//
// Created by pakamaka345 on 1/5/25.
//

#pragma once

class Map;

class MapDecorator
{
public:
	virtual void decorate(Map& map) = 0;
	virtual ~MapDecorator() = default;
};