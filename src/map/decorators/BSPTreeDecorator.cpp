//
// Created by pakamaka345 on 1/5/25.
//

#include "BSPTreeDecorator.hpp"

#include <map/Map.hpp>
#include <map/BSPTree.hpp>

BSPTreeDecorator::BSPTreeDecorator(int minLeafSize, int maxLeafSize)
	: minLeafSize(minLeafSize), maxLeafSize(maxLeafSize)
{
}

void BSPTreeDecorator::decorate(Map& map)
{
	BSPTree bspTree(map.getWidth(), map.getHeight());
	bspTree.generate(minLeafSize, maxLeafSize);

	auto leaves = bspTree.getLeaves();
	map.setLeaves(leaves);
}
