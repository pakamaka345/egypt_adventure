#include "GameView.hpp"

GameView::GameView(std::string pathToInitFile)
    : Map(pathToInitFile)
{
}

GameView::GameView(int width, int height)
    : Map(width, height)
{
}

void GameView::draw()
{
    std::cout << "----------------------------------------------------\n";
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {

        }
        std::cout << "\n";
    }
    //TODO after I add the player class and it will be dynamic
    // std::cout << "Piter Miller\n";
    // std::cout << "Info: \n";
    // std::cout << "Health: 100\n"; 
    // std::cout << "Ammo: 6/6\n";
    // std::cout << "light 1:14";
    // std::cout << "3 artifacts are active\n";
    // std::cout << "press 'I' to open inventory\n";
    // std::cout << "w,a,s,d to move\n";
    // std::cout << "'e' to interact\n";
    // Move to interface class
    std::cout << "----------------------------------------------------\n";
}