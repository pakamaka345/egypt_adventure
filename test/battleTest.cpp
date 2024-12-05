#include "BattleSystem.hpp"
#include "entities/Entity.hpp"
#include <iostream>

void displayMenu() {
    std::cout << "1. Show entities list" << std::endl;
    std::cout << "2. Add entity (input number)" << std::endl;
    std::cout << "3. Start battle" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    BattleSystem battleSystem("");
    auto entityList = battleSystem.getEntitiesList();

    std::cout << "Hello to the battle system!" << std::endl;
    std::cout << "It has been create to test how the battle system works." << std::endl;
    std::cout << "You should add 2 or more entities and start the battle." << std::endl;

    displayMenu();
    int choice;

    while (true) {
        std::cin >> choice;
        switch (choice) {
            case 1: {
                int i = 1;
                std::cout << "Entities list: " << std::endl;
                for (const auto &entity: entityList) {
                    std::cout << i << ". " << entity->getName() << " health: " << entity->getHealth() << std::endl;
                    i++;
                }
                displayMenu();
                break;
            }
            case 2: {
                std::cout << "Enter number of entities from 1 to " << entityList.size() << ": ";
                int number;
                std::cin >> number;
                if (number < 1 || number > entityList.size()) {
                    displayMenu();
                    break;
                }
                auto clonedEntity = entityList[number - 1]->clone();
                battleSystem.addEntityToBattle(clonedEntity);
                std::cout << "Enter your choice: ";
                break;
            }
            case 3: {
                try {
                    battleSystem.startBattle();
                    displayMenu();
                    break;
                } catch (std::runtime_error& e) {
                    std::cout << e.what() << std::endl;
                    displayMenu();
                    break;
                }
            }
            case 4: {
                return 0;
            }
            default: {
                std::cout << "Invalid choice" << std::endl;
                displayMenu();
                break;
            }
        }
    }
}