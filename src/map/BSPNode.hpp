//
// Created by pakamaka345 on 12/26/24.
//

#pragma once
#include <memory>

class BSPNode {
public:
    int x, y, width, height;
    std::shared_ptr<BSPNode> left, right;

    BSPNode(int x, int y, int width, int height);
    ~BSPNode() = default;

    bool isLeaf() const { return !left && !right; }

    bool split(int minSize);
};
