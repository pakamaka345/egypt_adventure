#pragma once
#include "entities/Entity.hpp"
#include "Inventory.hpp"

class Weapon;
class Bullet;
class Item;
class Amulet;

/**
 *  \brief Character class that will be used to create the main character.
 *  Could be changed later to a more generic class that will be used to create all entities similar to the player.
 *  Player will be a child class of this class with additional features.
 */
class Character : public Entity
{
private:
    std::shared_ptr<Weapon> revolver;
    Inventory inventory;
    /**
     * \brief A Torch shared pointer that will be used to store the character's torch that he equipped from the inventory.
     * Will be implemented later.
     *
     */
    // Torch activeTorch;
    /**
     * \brief A visibility range that will be used to understand how far the character can see.
     * will be changed if player has a active torch.
     */
    // int visibilityRange;

public:
    Character(const std::string& name, int x, int y, char symbol);
    ~Character() override = default;

    void reloadRevolver();

    void addToInventory(const std::shared_ptr<Item>& item);
    void removeFromInventory(const std::string& itemName);
    void useItemWithRemoving(const std::string& itemName, Entity& target);
    void useItem(const std::string& itemName, Entity& target);

    void attack(Entity& target) override;
    void takeDamage(float physicalDamage, float magicalDamage) override;
    void heal(float amount) override;
    void move(int dx, int dy) override;
    void update() override;
    std::shared_ptr<Entity> clone() const override;

    const Inventory& getInventory() const;
    const std::shared_ptr<Weapon>& getRevolver() const;
};