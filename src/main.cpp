#include <iostream>
#include <vector>

void displayMap(const std::vector<std::vector<char>>& map) {
    // Очищення екрана
    std::cout << "\033[2J\033[H";  // ANSI escape codes для очищення екрану

    for (const auto& row : map) {
        for (const auto& cell : row) {
            std::cout << cell;  // Виводимо символи карти
        }
        std::cout << std::endl;  // Перехід на новий рядок
    }
}

int main() {
    // Створюємо карту з використанням символу 178 для стін
    std::vector<std::vector<char>> map = {
        {char(178), char(178), char(178), char(178), char(178), char(178), char(178), char(178), char(178), char(178)},
        {char(178), ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', char(178)},
        {char(178), ' ', 'P', ' ', char(178), ' ', ' ', 'E', ' ', char(178)},
        {char(178), ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', char(178)},
        {char(178), char(178), char(178), char(178), char(178), char(178), char(178), char(178), char(178), char(178)}
    };

    // Виводимо карту
    displayMap(map);

    return 0;
}