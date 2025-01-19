#include "Inventory.hpp"
#include "../items/Item.hpp"
#include "../entities/Entity.hpp"
#include "../entities/Character.hpp"
#include "../states/GameState.hpp"
#include <stdexcept>

void Inventory::addItem(std::shared_ptr<Item> item) {
    if (
            const std::string name = item->getName();
            items.find(name) == items.end()
        ) {
        items[name].item = std::move(item);
        items[name].count = 1;
    } else {
        items[name].count++;
    }
}

void Inventory::removeItem(const std::string& itemName) {
    if (getItem(itemName) != std::nullopt) {
        if (items[itemName].count > 1) items[itemName].count--;
        else items.erase(itemName);
    } else {
        throw std::invalid_argument("Item not found in inventory");
    }
}

void Inventory::useItem(const std::string& itemName, const std::shared_ptr<Entity>& target) {
    if (getItem(itemName) != std::nullopt) {
        try {
            auto item = items[itemName].item;
            if (item->canBeUsedOnEnemies() && target == getCharacter()) {
                //TODO change to EventManager
                return;
            }

            item->use(*target);

            if (item->isConsumable()) {
                removeItem(itemName);
            }
        } catch (std::invalid_argument& e) {
            throw std::runtime_error("Failed to use item: " + std::string(e.what()));
            //TODO change to EventManager
        }
    } else {
        throw std::invalid_argument("Item not found in inventory to use");
        //TODO change to EventManager
    }
}

std::optional<std::shared_ptr<Item>> Inventory::getItem(const std::string& itemName) {
    auto it = items.find(itemName);
    if (it != items.end()) {
        return it->second.item;
    }
    return std::nullopt;
}

int Inventory::getItemCount(const std::string& itemName) {
    if (items.find(itemName) != items.end()) return items[itemName].count;
    else return 0;
}

bool Inventory::hasItem(const std::string& itemName) {
    return items.find(itemName) != items.end();
}

std::shared_ptr<Entity> Inventory::getCharacter() {
    return GameState::getInstance().getPlayer();
}
