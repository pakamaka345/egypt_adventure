//
// Created by pakamaka345 on 12/26/24.
//

#include "BSPTree.hpp"
#include <functional>

BSPTree::BSPTree(int width, int height)
{
	root = std::make_shared<BSPNode>(0, 0, width, height);
}

void BSPTree::generate(int minSize, int maxSize)
{
	std::vector<std::shared_ptr<BSPNode>> _leafs;
	_leafs.push_back(root);

	bool did_split = true;
	while (did_split) {
		did_split = false;
		std::vector<std::shared_ptr<BSPNode>> newLeaves;
		for (auto& leaf : _leafs) {
			if (leaf->left == nullptr && leaf->right == nullptr) {
				if (leaf->width > maxSize || leaf->height > maxSize || rand() % 100 > 25) {
					if (leaf->split(minSize)) {
						newLeaves.push_back(leaf->left);
						newLeaves.push_back(leaf->right);
						did_split = true;
					}
				}
			}
		}
		_leafs.insert(_leafs.end(), newLeaves.begin(), newLeaves.end());
	}
}

std::vector<std::shared_ptr<BSPNode>> BSPTree::getLeaves()
{
	std::vector<std::shared_ptr<BSPNode>> leaves;
	std::function<void(const std::shared_ptr<BSPNode>&)> traverser =
			[&](const std::shared_ptr<BSPNode>& node)
			{
				if (node->isLeaf()) {
					leaves.push_back(node);
				} else {
					traverser(node->left);
					traverser(node->right);
				}
			};

	traverser(root);
	return leaves;
}

