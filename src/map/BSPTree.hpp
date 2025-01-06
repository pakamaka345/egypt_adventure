//
// Created by pakamaka345 on 12/26/24.
//

#pragma once
#include <vector>
#include "map/BSPNode.hpp"

class BSPTree {
private:
	std::shared_ptr<BSPNode> root;

public:
	BSPTree(int width, int height);
	~BSPTree() = default;

	void generate(int minSize, int maxSize);

	std::vector<std::shared_ptr<BSPNode>> getLeaves();
};

