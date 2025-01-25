#include "entities/Entity.hpp"
#include <utility>
#include <commands/Command.hpp>
#include <map/Map.hpp>
#include <states/GameState.hpp>
#include <items/Bullet.hpp>
#include <dice/DiceRoll.hpp>
#include <items/Grenade.hpp>
#include <items/HealPotion.hpp>
#include <items/Torch.hpp>
#include "ai/AIComponent.hpp"
#include "items/amulets/Amulet.hpp"
#include <items/amulets/DamageAmulet.hpp>
#include <items/amulets/HealthAmulet.hpp>
#include <items/amulets/ArmorAmulets.hpp>
#include "modifiers/Modifier.hpp"

constexpr float BulletDamageMultiplier = 1.2f;

Entity::Entity(std::string  name, int attackRange,  float physicalDamage, float magicalDamage, float health, float defense, float priority,
               float dodgeChance, int x, int y, int z, char symbol)
               : name(std::move(name)), attackRange(attackRange), physicalDamage(physicalDamage), magicalDamage(magicalDamage), health(health), maxHealth(health), defense(defense), priority(priority), cooldown(0),
               dodgeChance(dodgeChance), aiComponent(nullptr), GameObject(x, y, z, symbol)
{
}



void Entity::addAmulet(const std::shared_ptr<Amulet>& amulet) {
    if (activeAmulets.size() >= 5) {
        throw std::runtime_error("All amulet slots are already occupied");
    }
    activeAmulets.push_back(amulet);
    amulet->applyAmuletEffect(*this);
}

void Entity::removeAmulet(const std::shared_ptr<Amulet>& amulet) {
    if (std::find(activeAmulets.begin(), activeAmulets.end(), amulet) == activeAmulets.end())
        throw std::invalid_argument("Amulet not found in active amulets");

    auto it = std::remove(activeAmulets.begin(), activeAmulets.end(), amulet);
    if (it != activeAmulets.end()) {
        activeAmulets.erase(it);
        amulet->removeAmuletEffect(*this);
    } else {
        throw std::runtime_error("Amulet not found in active amulets");
    }
}

void Entity::addModifier(const std::shared_ptr<Modifier>& modifier)
{
    activeModifiers.push_back(modifier);
}

void Entity::removeModifier(const std::shared_ptr<Modifier>& modifier)
{
    activeModifiers.erase(std::remove(activeModifiers.begin(), activeModifiers.end(), modifier), activeModifiers.end());
}

void Entity::applyEffects(const std::shared_ptr<Effect> &effect) {


    effectManager.addEffect(effect, *this);
}

void Entity::updateEffects() {
    effectManager.updateEffects(*this);
}

void Entity::removeEffects() {
    effectManager.clearEffects(*this);
}

bool Entity::isAlive() const {
    return health > 0;
}

bool Entity::canAttack(Entity &target) const {
    int radius = 0;

    if (posX == target.getX())
        radius = std::abs(posY - target.getY());
    else if (posY == target.getY())
        radius = std::abs(posX - target.getX());
    else
        return false;

    return radius <= attackRange;
}

bool Entity::isOnSameLevel(const std::shared_ptr<Entity>& other) const
{
    if (getZ() == other->getZ()) return true;
    return false;
}

int Entity::distanceTo(Entity &target) const {
    return static_cast<int>(sqrt(pow(target.getX() - getX(), 2) + pow(target.getY() - getY(), 2)));
}

void Entity::move(int dx, int dy)
{
    this->setX(this->getX() + dx);
    this->setY(this->getY() + dy);
}

void Entity::onDeath(GameState& gameState)
{
    const auto& level = gameState.getLevels().at(getZ());
    level->getMap()->removeEntity(getX(), getY());

    DiceRoll gen;

    int bulletAmount = gen.randomNumber(0, 5);
    for (int i = 0; i < bulletAmount; i++) {
        auto physDmg = static_cast<float>(gen.randomNumber(1, static_cast<int>(getMaxHealth()))) * BulletDamageMultiplier;
        auto magDmg = static_cast<float>(gen.randomNumber(1, static_cast<int>(getMaxHealth()))) * BulletDamageMultiplier;
        auto item = std::make_shared<Bullet>(physDmg, magDmg, getZ());
        item->setPos(getX(), getY(), getZ());
        level->addItem(item);
        level->getMap()->placeItem(getX(), getY(), item);
    }

    int chanceToDropTorch = gen.randomNumber(1, 10);
    if (chanceToDropTorch > 3) {
        auto torch = std::make_shared<Torch>(10, 12, getZ());
        torch->setPos(getX(), getY(), getZ());
        level->addItem(torch);
        level->getMap()->placeItem(getX(), getY(), torch);
    }
}

void Entity::update(GameState& gameState) {
    updateEffects();
    reduceCooldown();

    if (aiComponent) {
        auto command = aiComponent->makeDecision(gameState);
        if (command) {
            command->execute(gameState);
        }
    }
}

std::string &Entity::getName() {
    return name;
}

float Entity::getHealth() const {
    return health;
}

float Entity::getMaxHealth() const {
    float maxHealth = this->maxHealth;
    for (const auto& modifier : activeModifiers) {
        maxHealth = modifier->applyHealth(maxHealth);
    }

    return maxHealth;
}

int Entity::getAttackRange() const {
    return attackRange;
}

float Entity::getPhysicalDamage() const {
    float physicalDamage = this->physicalDamage;
    for (const auto& modifier : activeModifiers) {
        physicalDamage = modifier->applyPhysicalDamage(physicalDamage);
    }

    return physicalDamage;
}

float Entity::getMagicalDamage() const {
    float magicalDamage = this->magicalDamage;
    for (const auto& modifier : activeModifiers) {
        magicalDamage = modifier->applyMagicalDamage(magicalDamage);
    }

    return magicalDamage;
}

float Entity::getDefense() const {
    float defense = this->defense;
    for (const auto& modifier : activeModifiers) {
        defense = modifier->applyDefense(defense);
    }

    return defense;
}

float Entity::getPriority() const {
    float priority = this->priority;
    for (const auto& modifier : activeModifiers) {
        priority = modifier->applyPriority(priority);
    }

    return priority;
}

float Entity::getCooldown() const {
    return cooldown;
}

float Entity::getDodgeChance() const {
    float dodgeChance = this->dodgeChance;
    for (const auto& modifier : activeModifiers) {
        dodgeChance = modifier->applyDodgeChance(dodgeChance);
    }

    return dodgeChance;
}

Entity::AmuletList& Entity::getActiveAmulets() {
    return activeAmulets;
}

EffectManager &Entity::getEffectManager() {
    return effectManager;
}

Entity::ModifierList &Entity::getActiveModifiers() {
    return activeModifiers;
}

std::shared_ptr<AIComponent> Entity::getAIComponent() const
{
    return aiComponent;
}

void Entity::setHealth(float health) {
    Entity::health = health;
}

void Entity::setMaxHealth(float maxHealth) {
    Entity::maxHealth = maxHealth;
}

void Entity::setAttackRange(int attackRange) {
    Entity::attackRange = attackRange;
}

void Entity::setPhysicalDamage(float physicalDamage)
{
    Entity::physicalDamage = physicalDamage;
}

void Entity::setMagicalDamage(float magicalDamage)
{
    Entity::magicalDamage = magicalDamage;
}

void Entity::setDefense(float defense) {
    Entity::defense = defense;
}

void Entity::setPriority(float priority) {
    Entity::priority = priority;
}

void Entity::setCooldown(float cooldown) {
    Entity::cooldown = cooldown;
}

void Entity::setDodgeChance(float dodgeChance) {
    Entity::dodgeChance = dodgeChance;
}

void Entity::setAIComponent(const std::shared_ptr<AIComponent>& aiComponent)
{
    Entity::aiComponent = aiComponent;
}

void Entity::chanceToDropAmulets(const int chance, DiceRoll gen, const std::shared_ptr<LevelState>& level, const int gameLevel)
{
    int chanceToDropAmulet = gen.randomNumber(1, 10);
    if (chanceToDropAmulet > chance) {
        int whichAmulet = gen.randomNumber(1, 9);
        std::shared_ptr<Amulet> amulet;

        float multiplier = 1.0f + (gameLevel - 1) * 0.5f;

        if (whichAmulet <= 3) {
            auto defense = static_cast<float>(gen.randomNumber(1, 10)) / 100.0f * multiplier;
            auto dodgeChance = static_cast<float>(gen.randomNumber(1, 10)) / 100.0f * multiplier;
            amulet = std::make_shared<ArmorAmulets>(defense, dodgeChance, getZ());

        } else if (whichAmulet <= 6) {
            auto physDmg = static_cast<float>(gen.randomNumber(5, 20)) * multiplier;
            auto magDmg = static_cast<float>(gen.randomNumber(5, 20)) * multiplier;
            amulet = std::make_shared<DamageAmulet>(physDmg, magDmg, getZ());
        } else if (whichAmulet <= 9) {
            auto health = static_cast<float>(gen.randomNumber(10, 30)) * multiplier;
            amulet = std::make_shared<HealthAmulet>(health, getZ());
        }

        amulet->setPos(getX(), getY(), getZ());
        level->addItem(amulet);
        level->getMap()->placeItem(getX(), getY(), amulet);
    }
}

void Entity::chanceToDropGrenades(int chance, DiceRoll gen, const std::shared_ptr<LevelState>& level, int gameLevel)
{
    int chanceToDropGrenade = gen.randomNumber(1, 10);

    float multiplier = 1.0f + (gameLevel - 1);

    if (chanceToDropGrenade > chance) {
        float physDmg = static_cast<float>(gen.randomNumber(5, 20)) * multiplier;
        float magDmg = static_cast<float>(gen.randomNumber(5, 20)) * multiplier;
        int radius = gen.randomNumber(1, 5);
        auto grenade = std::make_shared<Grenade>(magDmg, physDmg, radius, getZ());
        grenade->setPos(getX(), getY(), getZ());
        level->addItem(grenade);
        level->getMap()->placeItem(getX(), getY(), grenade);
    }
}

void Entity::chanceToDropPotions(int chance, DiceRoll gen, const std::shared_ptr<LevelState>& level, int gameLevel)
{
    int chanceToDropPotion = gen.randomNumber(1, 10);
    float multiplier = 1.0f + (gameLevel - 1) * 0.5f;
    if (chanceToDropPotion > chance) {
        float healAmount = static_cast<float>(gen.randomNumber(5, 20)) * multiplier;
        auto healthPotion = std::make_shared<HealPotion>(healAmount, 3, getZ());
        healthPotion->setPos(getX(), getY(), getZ());
        level->addItem(healthPotion);
        level->getMap()->placeItem(getX(), getY(), healthPotion);
    }
}



