//
// Created by pakamaka345 on 12/26/24.
//

#pragma once
#include <memory>

class LevelState;

class MapGenerator {
private:
	MapGenerator() = default;

public:
	static std::shared_ptr<LevelState> GenerateMap(int levelIndex, int width, int height, int MinLeafSize, int MaxLeafSize, int MinRoomSize);
};

