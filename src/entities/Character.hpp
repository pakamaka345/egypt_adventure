#pragma once
#include "entities/Entity.hpp"
#include "utils/Inventory.hpp"
#include "items/Torch.hpp"

class Weapon;
class Bullet;
class Item;
class Amulet;
class Torch;

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
    std::unique_ptr<Torch> activeTorch;
    /**
     * \brief A visibility range that will be used to understand how far the character can see.
     * will be changed if player has a active torch.
     */
    int visibilityRange;

public:
    Character(const std::string& name, int x, int y, int z, char symbol);
    Character(const Character& other);
    ~Character() override = default;

    void reloadRevolver();

    void addToInventory(const std::shared_ptr<Item>& item);
    void removeFromInventory(const std::string& itemName);

    void attack(Entity& target) override;
    void takeDamage(float physicalDamage, float magicalDamage) override;
    void heal(float amount) override;
    void move(int dx, int dy) override;
    void update(GameState& gameState) override;
    void onDeath(GameState& gameState) override;
    std::shared_ptr<Entity> clone() const override;

    Inventory& getInventory();
    const std::shared_ptr<Weapon>& getRevolver() const;

    float getPhysicalDamage() const override;
    float getMagicalDamage() const override;

    void setActiveTorch(std::unique_ptr<Torch> torch);
    int getVisibilityRange() const;

private:
    void updateLight(GameState& gameState);
    void deleteLight(int x, int y, GameState& gameState) const;
    void createLight(int x, int y, GameState& gameState) const;

    void updateAttackRange();
};