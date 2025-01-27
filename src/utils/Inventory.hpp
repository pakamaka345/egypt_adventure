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
    Inventory() = default;
    ~Inventory() = default;

    void addItem(std::shared_ptr<Item> item);
    void removeItem(const std::string& itemName);
    void useItem(const std::string& itemName, const std::shared_ptr<Entity>& target = getCharacter());

    std::optional<std::shared_ptr<Item>> getItem(const std::string& itemName);
    int getItemCount(const std::string& itemName);
    std::unordered_map<std::string, InventoryItem> getItems() const { return items; }
    int getItemsCount() const;
    bool hasItem(const std::string& itemName);

    static std::shared_ptr<Entity> getCharacter();
};