//
// Created by pakamaka345 on 12/26/24.
//

#include "BSPNode.hpp"
#include <dice/DiceRoll.hpp>

BSPNode::BSPNode(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height), left(nullptr), right(nullptr)
{
}

bool BSPNode::split(const int minSize)
{
    DiceRoll gen;
    if (left != nullptr || right != nullptr) return false;

    bool splitHorizontal = gen.randomNumber(0, 1) == 0;
    if (width > height && static_cast<float>(width) / static_cast<float>(height) >= 1.25) splitHorizontal = false;
    else if (height > width && static_cast<float>(height) / static_cast<float>(width) >= 1.25) splitHorizontal = true;

    int maxSize = (splitHorizontal ? height : width) - minSize;

    if (maxSize <= minSize) return false;

    int splitPos = gen.randomNumber(minSize, maxSize);

    if (splitHorizontal) {
        left = std::make_shared<BSPNode>(x, y, width, splitPos);
        right = std::make_shared<BSPNode>(x, y + splitPos, width, height - splitPos);
    } else {
        left = std::make_shared<BSPNode>(x, y, splitPos, height);
        right = std::make_shared<BSPNode>(x + splitPos, y, width - splitPos, height);
    }

    return true;
}

