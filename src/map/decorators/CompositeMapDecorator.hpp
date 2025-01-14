//
// Created by pakamaka345 on 1/5/25.
//

#pragma once
#include <vector>
#include <memory>
#include "MapDecorator.hpp"

class CompositeMapDecorator : public MapDecorator {
	std::vector<std::unique_ptr<MapDecorator>> decorators;

public:
	void addDecorator(std::unique_ptr<MapDecorator> decorator) {
		decorators.push_back(std::move(decorator));
	}

	void decorate(Map& map) override {
		for (auto& decorator : decorators) {
			decorator->decorate(map);
		}

		decorators.clear();
	}

};
