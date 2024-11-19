#include <iostream>
#include <memory>
#include <string>
#include "GameView.hpp"
#include "entities/Player.hpp"
#include "items/Torch.hpp"


void displayMenu() {
    std::cout << "-------------------------------------\n";
    std::cout << "Commands:\n";
    std::cout << "1. Place item\n";
    std::cout << "2. Place entity\n";
    std::cout << "3. Remove item\n";
    std::cout << "4. Remove entity\n";
    std::cout << "5. Change tile type\n";
    std::cout << "6. Display information about entities and items\n";
    std::cout << "7. Show map\n";
    std::cout << "0. Exit\n";
    std::cout << "-------------------------------------\n";
}

void runInterface(Map& map) {
    int choice;
    while (true) {
        displayMenu();
        std::cout << "Your choice: ";
        std::cin >> choice;

        if (choice == 0) {
            break; 
        }

        int x, y;
        std::string name;
        char symbol;

        try {
            switch (choice) {
                case 1: 
                    std::cout << "Enter coordinates (x y): ";
                    std::cin >> x >> y;
                    std::cout << "Enter item name: ";
                    std::cin >> name;
                    std::cout << "Enter item symbol: ";
                    std::cin >> symbol;
                    map.placeItem(x, y, std::make_unique<Torch>(name, 1, true, symbol, x, y));
                    std::cout << "Item placed at (" << x << ", " << y << ").\n";
                    break;

                case 2: 
                    std::cout << "Enter coordinates (x y): ";
                    std::cin >> x >> y;
                    std::cout << "Enter entity name: ";
                    std::cin >> name;
                    std::cout << "Enter entity symbol: ";
                    std::cin >> symbol;
                    map.placeEntity(x, y, std::make_unique<Player>(name, 100, 10, symbol, x, y));
                    std::cout << "Entity placed at (" << x << ", " << y << ").\n";
                    break;

                case 3: 
                    std::cout << "Enter coordinates (x y): ";
                    std::cin >> x >> y;
                    map.removeItem(x, y);
                    std::cout << "Item removed from (" << x << ", " << y << ").\n";
                    break;

                case 4: 
                    std::cout << "Enter coordinates (x y): ";
                    std::cin >> x >> y;
                    map.removeEntity(x, y);
                    std::cout << "Entity removed from (" << x << ", " << y << ").\n";
                    break;

                case 5:
                    std::cout << "Enter coordinates (x y): ";
                    std::cin >> x >> y;
                    int tileType;
                    std::cout << "Enter tile type (0 - floor, 1 - wall): ";
                    std::cin >> tileType;
                    map.setTile(x, y, static_cast<TileType::TileType>(tileType));
                    std::cout << "Tile type changed at (" << x << ", " << y << ").\n";
                    break;

                case 6: 
                    map.listEntitiesAndItems("../assets/maps/list.txt");
                    std::cout << "Information about entities and items has been saved to the file.\n";
                    break;

                case 7: 
                    map.draw();
                    break;

                default:
                    std::cout << "Invalid choice, please try again.\n";
                    break;
            }
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

int main() {
    //std::locale::global(std::locale("en_US.UTF-8"));

    try {
        GameView map("../assets/maps/map.txt"); 

        runInterface(map); 
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}