//
// Created by pakamaka345 on 1/30/25.
//

#include "TutankhamunsСrown.hpp"

#include "states/GameState.hpp"

TutankhamunsСrown::TutankhamunsСrown(int levelIndex)
	: Item("tutankhamuns crown", "A crown worn by the ancient Pharaoh Tutankhamun, said to bestow wisdom and power upon its wearer.", 0, 0, levelIndex, 'c')
{
}

void TutankhamunsСrown::use(Entity& target)
{
	GameState::getInstance().setIsGameOver(true);
}

std::string TutankhamunsСrown::getSpecifications()
{
	return "The ultimate goal of the hero. Using this item ends the game.";
}
