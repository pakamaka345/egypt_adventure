#pragma once
#include <unordered_map>
#include <string>
#include <utility>
#include <memory>
#include <optional>

class Item;
class Entity;

class Inventory
{
private:
    struct InventoryItem {
        std::shared_ptr<Item> item;
        int count;
    };

private:
    std::unordered_map<std::string, InventoryItem> items;

public:
    Inventory();
    ~Inventory() = default;

    void addItem(const std::shared_ptr<Item>& item);
    void removeItem(const std::string& itemName);
    void useItemWithRemoving(const std::string& itemName, Entity& target);
    void useItem(const std::string& itemName, Entity& target);

    std::optional<std::shared_ptr<Item>> getItem(const std::string& itemName);
    int getItemCount(const std::string& itemName);
    std::unordered_map<std::string, InventoryItem> getItems() const { return items; }
    bool hasItem(const std::string& itemName);
};