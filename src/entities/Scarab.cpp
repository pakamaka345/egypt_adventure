#include "entities/Scarab.hpp"
#include <effects/GroupAttackBonus.hpp>
#include <states/GameState.hpp>
#include <map/Map.hpp>
#include <items/Bullet.hpp>
#include <ai/AIComponent.hpp>
#include <dice/DiceRoll.hpp>
#include <items/amulets/ArmorAmulets.hpp>
#include <items/amulets/DamageAmulet.hpp>
#include <items/amulets/HealthAmulet.hpp>

constexpr float BulletDamageMultiplier = 1.2f;

Scarab::Scarab(const std::string &name, int attackRange, float physicalDamage, float magicalDamage, float health, float defense,
               float priority, float dodgeChance, int x, int y, int z, char symbol)
               : groupAttackBonus(1.0f),
               Entity(name, attackRange, physicalDamage, magicalDamage, health, defense, priority, dodgeChance, x, y, z, symbol)
{
    aiComponent = std::make_shared<AIComponent>();
}

void Scarab::attack(Entity &target) {
    if (isReady()) {
        if (canAttack(target)) {
            DiceRoll dice(8);
            int diceRoll = dice.roll();
            float physicalDamage = (getPhysicalDamage() * float(diceRoll) / 4.0f) * (1.0f - target.getDefense()) * groupAttackBonus;
            target.takeDamage(physicalDamage, getMagicalDamage());
            resetCooldown(this->getPriority());
        }
    } else {
        throw std::runtime_error("Scarab is on cooldown");
    }
}

void Scarab::takeDamage(float physicalDamage, float magicalDamage) {
    health = std::max(0.0f, (health - physicalDamage - magicalDamage));
}

void Scarab::heal(float amount) {
    health = std::min(getMaxHealth(), (health + amount));
}

void Scarab::move(int dx, int dy) {
    Entity::move(dx, dy);
}

void Scarab::update(GameState& gameState) {
    Entity::update(gameState);

    findNearestScarabs(*gameState.getCurrentLevel().getMap());
}

void Scarab::findNearestScarabs(const Map& map)
{
    std::vector<std::shared_ptr<Scarab>> scarabs;
    for (int dx = getX() - 1; dx <= getX() + 1; dx++) {
        for (int dy = getY() - 1; dy <= getY() + 1; dy++) {
            if (dx == getX() && dy == getY()) continue;
            if (map.isInsideMap(dx, dy)) {
                if (auto scarab = std::dynamic_pointer_cast<Scarab>(map.getEntityAt(dx, dy))) {
                    scarabs.push_back(scarab);
                }
            }
        }
    }

    for (int i = 0; i < scarabs.size(); i++) {
        this->applyEffects(std::make_shared<GroupAttackBonus>(1, 1.1f));
    }
}

void Scarab::onDeath(GameState& gameState)
{
    Entity::onDeath(gameState);

    DiceRoll gen;
    int bulletAmount = gen.randomNumber(0, 5);
    const auto& level = gameState.getLevels()[getZ()];
    for (int i = 0; i < bulletAmount; i++) {
        auto physDmg = static_cast<float>(gen.randomNumber(1, static_cast<int>(getMaxHealth()))) * BulletDamageMultiplier;
        auto item = std::make_shared<Bullet>(physDmg, 0, getZ());
        item->setPos(getX(), getY(), getZ());
        level->addItem(item);
        level->getMap()->placeItem(getX(), getY(), item);
    }

    int chanceToDropAmulet = gen.randomNumber(1, 10);
    if (chanceToDropAmulet > 5) {
        int whichAmulet = gen.randomNumber(1, 10);
        std::shared_ptr<Amulet> amulet;
        if (whichAmulet <= 3) {
            auto defense = static_cast<float>(gen.randomNumber(1, 15)) / 100.0f;
            auto dodgeChance = static_cast<float>(gen.randomNumber(1, 15)) / 100.0f;
            amulet = std::make_shared<ArmorAmulets>(defense, dodgeChance, getZ());

        } else if (whichAmulet <= 6) {
            auto physDmg = static_cast<float>(gen.randomNumber(1, 15));
            auto magDmg = static_cast<float>(gen.randomNumber(1, 15));
            amulet = std::make_shared<DamageAmulet>(physDmg, magDmg, getZ());
        } else if (whichAmulet <= 9) {
            auto health = static_cast<float>(gen.randomNumber(1, 15));
            amulet = std::make_shared<HealthAmulet>(health, getZ());
        }

        amulet->setPos(getX(), getY(), getZ());
        level->addItem(amulet);
        level->getMap()->placeItem(getX(), getY(), amulet);
    }
}


std::shared_ptr<Entity> Scarab::clone() const {
    return std::make_shared<Scarab>(*this);
}

void Scarab::setGroupAttackBonus(float bonus) {
    groupAttackBonus = bonus;
}

float Scarab::getGroupAttackBonus() const {
    return groupAttackBonus;
}

