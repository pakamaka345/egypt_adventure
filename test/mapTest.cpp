#include <iostream>
#include <memory>
#include <cassert>
#include "Map.hpp"
#include "Item.hpp"
#include "Entity.hpp"

void testPlaceItem() {
    Map map(5, 5);
    auto item = std::make_unique<Item>("Torch", 1, true, 'T');

    map.placeItem(2, 2, std::move(item));
    assert(map.canPlaceItem(2, 2) == false); 

    std::cout << "testPlaceItem passed!\n";
}

void testRemoveItem() {
    Map map(5, 5);
    auto item = std::make_unique<Item>("Torch", 1, true, 'T');
    map.placeItem(2, 2, std::move(item));

    map.removeItem(2, 2);
    assert(map.canPlaceItem(2, 2) == true); 

    std::cout << "testRemoveItem passed!\n";
}

void testPlaceEntity() {
    Map map(5, 5);
    auto entity = std::make_unique<Monster>("Skeleton", 30, 5, 'G');

    map.placeEntity(3, 3, std::move(entity));
    assert(map.canPlaceEntity(3, 3) == false); 

    std::cout << "testPlaceEntity passed!\n";
}

void testRemoveEntity() {
    Map map(5, 5);
    auto entity = std::make_unique<Monster>("Mumia", 30, 5, 'G');
    map.placeEntity(3, 3, std::move(entity));

    map.removeEntity(3, 3);
    assert(map.canPlaceEntity(3, 3) == true);

    std::cout << "testRemoveEntity passed!\n";
}

void testListEntitiesAndItems() {
    Map map(5, 5);
    map.placeItem(1, 1, std::make_unique<Potion>("Health Potion", 1, true, 'H'));
    map.placeEntity(2, 2, std::make_unique<Person>("Piter Miller", 100, 10, 'H'));

    map.listEntitiesAndItems("../assets/maps/list.txt");

    std::cout << "testListEntitiesAndItems executed. Please check the output file for correctness.\n";
}

void testDrawMap() {
    Map map(5, 5);
    map.placeItem(0, 0, std::make_unique<Ammo>("Ammo", 1, true, 'S'));
    map.placeEntity(1, 1, std::make_unique<Player>("Piter Miller", 50, 10, 'K'));

    map.draw();

    std::cout << "testDrawMap executed. Check console output for map.\n";
}

int main() {
    testPlaceItem();
    testRemoveItem();
    testPlaceEntity();
    testRemoveEntity();
    testListEntitiesAndItems();
    testDrawMap();

    std::cout << "All tests executed!\n";

    return 0;
}