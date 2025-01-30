//
// Created by pakamaka345 on 1/30/25.
//

#include "TutankhamunsCrown.hpp"

#include "states/GameState.hpp"

TutankhamunsCrown::TutankhamunsCrown(int levelIndex)
	: Item("tutankhamuns crown", "A crown worn by the ancient Pharaoh Tutankhamun, said to bestow wisdom and power upon its wearer.", 0, 0, levelIndex, 'c')
{
}

void TutankhamunsCrown::use(Entity& target)
{
	GameState::getInstance().setIsGameOver(true);
}

std::string TutankhamunsCrown::getSpecifications()
{
	return "The ultimate goal of the hero. Using this item ends the game.";
}
