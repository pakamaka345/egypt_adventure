#include "Inventory.hpp"
#include <stdexcept>

Inventory::Inventory() : items()
{
}

void Inventory::addItem(const std::shared_ptr<Item>& item) {
    std::string name = item->getName();
    if (items.find(name) == items.end()) {
        items[name].item = item;
        items[name].count = 1;
    } else {
        items[name].count++;
    }
}

void Inventory::removeItem(const std::string& itemName) {
    if (getItem(itemName) != std::nullopt) {
        int count = items[itemName].count;
        if (count > 1) items[itemName].count--;
        else items.erase(itemName);
    } else {
        throw std::invalid_argument("Item not found in inventory");
    }
}

void Inventory::useItemWithRemoving(const std::string &itemName, Entity& target) {
    if (getItem(itemName) != std::nullopt) {
        items[itemName].item->use(target);
        removeItem(itemName);
    } else {
        throw std::invalid_argument("Item not found in inventory to use");
    }
}

void Inventory::useItem(const std::string &itemName, Entity &target) {
    if (getItem(itemName) != std::nullopt) {
        items[itemName].item->use(target);
    } else {
        throw std::invalid_argument("Item not found in inventory to use");
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

bool Inventory::hasItem(const std::string &itemName) {
    return items.find(itemName) != items.end();
}
