#pragma once
#include <memory>

class GameState;
class Character;

class GameView {
private:
	int viewportWidth;
	int viewportHeight;

public:
	GameView(int width, int height);
    ~GameView() = default;

    void render(GameState& gameState);

private:
	void appendPlayerStatsRow(std::ostringstream& row, int y, int startY, const std::shared_ptr<Character>& player);
};

