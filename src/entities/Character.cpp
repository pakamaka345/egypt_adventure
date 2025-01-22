#include "entities/Character.hpp"
#include <dice/DiceRoll.hpp>
#include <utility>
#include <map/Map.hpp>
#include <states/GameState.hpp>

#include "items/Bullet.hpp"
#include "weapons/Weapon.hpp"
#include "modifiers/Modifier.hpp"

Character::Character(const std::string &name, int x, int y, int z, char symbol)
    : revolver(std::make_shared<Weapon>("Revolver", 6))
    , activeTorch(nullptr)
    , visibilityRange(4)
    , Entity(name, 5, 10.0f, 0.0f, 50.0f, 0.3f, 2.0f, 0.2f, x, y, z, symbol)
{
}

Character::Character(const Character& other) : Entity(other)
{
    this->revolver = other.getRevolver();
    this->activeTorch = nullptr;
    this->visibilityRange = 4;
}


void Character::reloadRevolver() {
    try {
        while (revolver->getAmmo() < revolver->getMagazineSize() && inventory.hasItem("bullet")) {
            inventory.useItem("bullet");
        }
    } catch (const std::invalid_argument& e) {
        throw std::runtime_error("No bullets in inventory");
    }
}

void Character::addToInventory(const std::shared_ptr<Item> &item) {
    inventory.addItem(item);
}

void Character::removeFromInventory(const std::string &itemName) {
    inventory.removeItem(itemName);
}

void Character::attack(Entity &target) {
    if (isReady()) {
        DiceRoll gen;

        int diceRoll = gen.randomNumber(1, 8);

        float physicalDamage = (getPhysicalDamage() * static_cast<float>(diceRoll) / 4.0f) * (1 - target.getDefense());

        if (revolver->getAmmo() > 0) {
            this->attackRange = 5.0f;
            revolver->shoot();
        } else {
            this->attackRange = 1.0f;
        }

        if (canAttack(target)) {
            target.takeDamage(physicalDamage, getMagicalDamage());
            resetCooldown(this->getPriority());
        }

    } else {
        throw std::runtime_error("Character is on cooldown");
    }
}

void Character::takeDamage(float physicalDamage, float magicalDamage) {
    health = std::max(0.0f, (health - physicalDamage - magicalDamage));
}

void Character::heal(float amount) {
    health = std::min(maxHealth, (health + amount));
}

void Character::move(int dx, int dy) {
    auto& gameState = GameState::getInstance();

    deleteLight(getX(), getY(), gameState);

    setX(getX() + dx);
    setY(getY() + dy);

    createLight(getX(), getY(), gameState);
}

void Character::update(GameState& gameState) {
    Entity::update(gameState);

    updateLight(gameState);
}

void Character::updateLight(GameState& gameState)
{
    deleteLight(getX(), getY(), gameState);

    if (activeTorch == nullptr) visibilityRange = 4;
    else {
        visibilityRange = activeTorch->getRadius();
        if (activeTorch->decreaseDuration() <= 0) {
            activeTorch = nullptr;
        }
    }

    createLight(getX(), getY(), gameState);
}

void Character::deleteLight(const int x, const int y, GameState& gameState) const
{
    const auto map = gameState.getCurrentLevel().getMap();

    for (int nx = x - visibilityRange; nx <= x + visibilityRange; nx++) {
        for (int ny = y - visibilityRange; ny <= y + visibilityRange; ny++) {
            if (map->isInsideMap(nx, ny)) {
                if (map->getLightType(nx, ny) == LightType::DYNAMIC) {
                    map->setLightMap(nx, ny, LightType::NONE);
                }
            }
        }
    }
}

void Character::createLight(const int x, const int y, GameState& gameState) const
{
    const auto map = gameState.getCurrentLevel().getMap();

    for (int nx = x - visibilityRange; nx <= x + visibilityRange; nx++) {
        for (int ny = y - visibilityRange; ny <= y + visibilityRange; ny++) {
            if (map->isInsideMap(nx, ny)) {
                if (map->getLightType(nx, ny) == LightType::NONE) {
                    map->setLightMap(nx, ny, LightType::DYNAMIC);
                }
            }
        }
    }
}


std::shared_ptr<Entity> Character::clone() const {
    return std::make_shared<Character>(*this);
}

Inventory &Character::getInventory() {
    return inventory;
}

const std::shared_ptr<Weapon> &Character::getRevolver() const {
    return revolver;
}

float Character::getPhysicalDamage() const
{
    float physicalDamage = 0.0f;
    if (revolver->getAmmo() > 0) {
        auto& bullet = revolver->getMagazine().front();
        physicalDamage = bullet->getPhysicalDamage();
    } else {
        physicalDamage = this->physicalDamage;
    }

    for (const auto& modifier : activeModifiers) {
        physicalDamage = modifier->applyPhysicalDamage(physicalDamage);
    }

    return physicalDamage;
}

float Character::getMagicalDamage() const
{
    float magicalDamage = 0.0f;
    if (revolver->getAmmo() > 0) {
        auto& bullet = revolver->getMagazine().front();
        magicalDamage = bullet->getMagicalDamage();
    } else {
        magicalDamage = this->magicalDamage;
    }

    for (const auto& modifier : activeModifiers) {
        magicalDamage = modifier->applyMagicalDamage(magicalDamage);
    }

    return magicalDamage;
}

void Character::setActiveTorch(std::unique_ptr<Torch> torch)
{
    activeTorch = std::move(torch);
}

int Character::getVisibilityRange() const
{
    return visibilityRange;
}




