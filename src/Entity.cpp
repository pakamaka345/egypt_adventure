#include "entities/Entity.hpp"
#include "items/amulets/Amulet.hpp"

Entity::Entity(const std::string& name, int attackRange,  float attackDamage, float health, float defense, float priority,
               float dodgeChance, int x, int y, char symbol)
               : name(name), attackRange(attackRange), attackDamage(attackDamage), health(health), maxHealth(health), defense(defense), priority(priority), cooldown(0),
               dodgeChance(dodgeChance), activeAmulets(), GameObject(x, y, symbol)
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

void Entity::applyEffects(const std::shared_ptr<Effect> &effect) {
    effectManager.addEffect(effect, *this);
}

void Entity::updateEffects() {
    effectManager.updateEffects(*this);
}

void Entity::removeEffects() {
    effectManager.clearEffects(*this);
}

bool Entity::canBePlacedOn(TileType::Type tileType) const {
    return tileType == TileType::Type::FLOOR;
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

void Entity::update() {
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
    return maxHealth;
}

int Entity::getAttackRange() const {
    return attackRange;
}

float Entity::getAttackDamage() const {
    return attackDamage;
}

float Entity::getDefense() const {
    return defense;
}

float Entity::getPriority() const {
    return priority;
}

float Entity::getCooldown() const {
    return cooldown;
}

float Entity::getDodgeChance() const {
    return dodgeChance;
}

Entity::AmuletList& Entity::getActiveAmulets() {
    return activeAmulets;
}

EffectManager &Entity::getEffectManager() {
    return effectManager;
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

void Entity::setAttackDamage(float attackDamage) {
    Entity::attackDamage = attackDamage;
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


