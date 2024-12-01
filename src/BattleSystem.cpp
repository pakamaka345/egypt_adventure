#include "BattleSystem.hpp"
#include <random>
#include <fstream>
#include <iostream>

BattleSystem::BattleSystem(const std::string &pathToInitFile) {
    readEntitiesFromFile(pathToInitFile);
}

void BattleSystem::addEntityToList(const std::shared_ptr<Entity> &entity) {
    entitiesList.push_back(entity);
}

void BattleSystem::removeEntityFromList(const std::shared_ptr<Entity> &entity) {
    auto it = std::remove(entitiesList.begin(), entitiesList.end(), entity);
    if (it != entitiesList.end()) {
        entitiesList.erase(it, entitiesList.end());
    }
}

void BattleSystem::addEntityToBattle(const std::shared_ptr<Entity>& entity) {
    queue.addEntity(entity);
}

void BattleSystem::removeEntityFromBattle(const std::shared_ptr<Entity> &entity) {
    queue.removeEntity(entity);
}

void BattleSystem::clearBattle() {
    queue.clear();
}

void BattleSystem::startBattle() {
    int counter = 1;
    while (queue.size() > 1) {
        auto attacker = queue.popEntity();
        if (!attacker->isAlive()) {
            std::cout << attacker->getName() << " is dead" << std::endl;
            continue;
        }

        auto target = findTarget();
        if (target == nullptr) {
            throw std::runtime_error("No target found");
        }

        // Calculate if attacker hits target like in dnd
        // if he fails then he can also try to roll a dice (10& chance) if he has (<75% health) to take a potion (amount 0 - 25 hp)
        // he also can try to run away (5% chance)
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(1, 20);
        double roll = dis(gen) / 20.0f;
        double attackRoll = attacker->getAttackDamage() / 100.0f;
        double defense = target->getDodgeChance();
        if (roll + attackRoll < defense) {
            try {
                attacker->attack(*target);
                std::cout << attacker->getName() << " attacks " << target->getName() << ". Target`s health: " << target->getHealth() << std::endl;
            } catch (const std::runtime_error& e) {
                std::cout << e.what() << std::endl;
                queue.addEntity(attacker);
                continue;
            }
        } else {
            std::uniform_real_distribution<> heal(1, 100);
            double healRoll = heal(gen) / 100.0f;
            if (attacker->getHealth() / attacker->getMaxHealth() < 0.75 && roll <= 0.25) {
                std::uniform_real_distribution<> amount(0, 25);
                attacker->heal(float(amount(gen)));
                std::cout << attacker->getName() << " heals himself. Health: " << attacker->getHealth() << "/" << attacker->getMaxHealth() << std::endl;
            }
            std::uniform_real_distribution<> run(1, 100);
            double runRoll = run(gen) / 100.0f;
            if (roll <= 0.05) {
                std::cout << attacker->getName() << " runs away" << std::endl;
                continue;
            }
        }

        queue.addEntity(attacker);
        counter++;
    }

    std::cout << "Battle ended" << std::endl;
    std::cout << "Winner: " << queue.popEntity()->getName() << std::endl;
    std::cout << "Number of turns: " << counter << std::endl;
}

std::vector<std::shared_ptr<Entity>>& BattleSystem::getEntitiesList() {
    return entitiesList;
}

std::shared_ptr<Entity> BattleSystem::findTarget() {
    std::vector<std::shared_ptr<Entity>> entities;
    while (!queue.isEmpty()) {
        auto entity = queue.popEntity();
        if (entity->isAlive()) {
            for (const auto& e : entities) queue.addEntity(e);
            queue.addEntity(entity);
            return entity;
        }
        entities.push_back(entity);
    }

    for (const auto& e : entities) queue.addEntity(e);
    return nullptr;
}