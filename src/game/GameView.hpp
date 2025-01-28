#pragma once
#include <memory>

class ThrowableItem;
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
	void renderInventory(GameState& gameState) const;
	void renderAmuletMenu(GameState& gameState) const;
	void handleThrowableItem(GameState& gameState, std::shared_ptr<ThrowableItem> item) const;

private:
	void appendPlayerStatsRow(std::ostringstream& row, int y, int startY, const std::shared_ptr<Character>& player);
};

