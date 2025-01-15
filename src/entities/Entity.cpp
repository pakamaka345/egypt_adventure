#include "entities/Entity.hpp"

#include <utility>
#include "items/amulets/Amulet.hpp"
#include "modifiers/Modifier.hpp"

Entity::Entity(std::string  name, int attackRange,  float physicalDamage, float magicalDamage, float health, float defense, float priority,
               float dodgeChance, int x, int y, char symbol)
               : name(std::move(name)), attackRange(attackRange), physicalDamage(physicalDamage), magicalDamage(magicalDamage), health(health), maxHealth(health), defense(defense), priority(priority), cooldown(0),
               dodgeChance(dodgeChance), GameObject(x, y, symbol)
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

int Entity::distanceTo(Entity &target) const {
    if (target.getX() == this->getX()) {
        return std::abs(target.getY() - this->getY());
    } else if (target.getY() == this->getY()) {
        return std::abs(target.getX() - this->getX());
    }
    return -1;
}

void Entity::move(int dx, int dy)
{
    this->setX(this->getX() + dx);
    this->setY(this->getY() + dy);
}


void Entity::update(Map& map) {
    updateEffects();
    reduceCooldown();
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


