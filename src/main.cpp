#include <iostream>
#include <memory>
#include <string>
#include "Item.hpp"
#include "Entity.hpp"
#include "Map.hpp"

void displayMenu() {
    std::cout << "-------------------------------------\n";
    std::cout << "Commands:\n";
    std::cout << "1. Place item\n";
    std::cout << "2. Place entity\n";
    std::cout << "3. Remove item\n";
    std::cout << "4. Remove entity\n";
    std::cout << "5. Display information about entities and items\n";
    std::cout << "6. Show map\n";
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

        switch (choice) {
            case 1: 
                std::cout << "Enter coordinates (x y): ";
                std::cin >> x >> y;
                std::cout << "Enter item name: ";
                std::cin >> name;
                std::cout << "Enter item symbol: ";
                std::cin >> symbol;
                map.placeItem(x, y, std::make_unique<Item>(name, 1, true, symbol));
                std::cout << "Item placed at (" << x << ", " << y << ").\n";
                break;

            case 2: 
                std::cout << "Enter coordinates (x y): ";
                std::cin >> x >> y;
                std::cout << "Enter entity name: ";
                std::cin >> name;
                std::cout << "Enter entity symbol: ";
                std::cin >> symbol;
                map.placeEntity(x, y, std::make_unique<Entity>(name, 100, 10, symbol));
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
                map.listEntitiesAndItems("../assets/maps/list.txt");
                std::cout << "Information about entities and items has been saved to the file.\n";
                break;

            case 6: 
                map.draw();
                break;

            default:
                std::cout << "Invalid choice, please try again.\n";
                break;
        }
    }
}

int main() {
    Map map("../assets/maps/map.txt"); 

    runInterface(map); 

    return 0;
}