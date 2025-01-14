#include "BattleSystem.hpp"
#include "entities/Entity.hpp"
#include "entities/Character.hpp"
#include "entities/Scarab.hpp"
#include "entities/Skeleton.hpp"
#include "entities/Mummy.hpp"
#include "entities/Phantom.hpp"
#include "entities/SandGolem.hpp"
#include "items/Bullet.hpp"
#include "config/Config.hpp"
#include "dice/DiceRoll.hpp"
#include <random>
#include <iostream>
#include <map>
#include <states/GameState.hpp>

BattleSystem::BattleSystem(const std::string &pathToInitFile)
{
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

void BattleSystem::startBattle(int rounds) {
    std::map<int, std::shared_ptr<Entity>> winners;
    std::map<std::string, int> countWins;

    DiceRoll dice(20);

    std::vector<std::shared_ptr<Entity>> entities;

    for (int i = 0; i < queue.size(); i++) {
        auto entity = queue.entityAt(i);
        entities.push_back(entity->clone());
    }

    for (int i = 0; i < rounds; ++i) {
        int round = i + 1;
        while (queue.size() > 1) {
            auto attacker = queue.popEntity();
            auto target = findTarget();
            if (target == nullptr) {
                break;
            }
            double attackMod = attacker->getPhysicalDamage() / 100.0f + attacker->getMagicalDamage() / 100.0f;
            double defenseMod = target->getDodgeChance() + target->getDefense();
            double attackRoll = double(dice.roll()) / 20.0f + attackMod;

            try {
                if (attackRoll > defenseMod)
                {
                    if (attacker->isAlive() && target->isAlive()) {
                        attacker->attack(*target);
                        if (!target->isAlive()) {
                            if (queue.size() == 1) {
                                removeEntityFromBattle(target);
                                winners[round] = attacker;
                                countWins[attacker->getName()]++;

                                break;
                            }
                        }
                    }
                }
            } catch (const std::exception& e) {
                queue.addEntity(attacker);
                continue;
            }

            queue.addEntity(attacker);
            updateEntities();
        }

        clearBattle();
        for (const auto& entity : entities) {
            queue.addEntity(entity->clone());
        }
    }

    std::cout << "Battle is over!" << std::endl;
    for (const auto& winner : winners) {
        std::cout << "Round " << winner.first << ": " << winner.second->getName() << " wins! " << std::endl;
    }

    for (const auto& entityCount : countWins) {
        std::cout << entityCount.first << " wins: " << entityCount.second << " times" << std::endl;
    }

    clearBattle();
}

std::vector<std::shared_ptr<Entity>>& BattleSystem::getEntitiesList() {
    return entitiesList;
}

std::shared_ptr<Entity> BattleSystem::findTarget() {
    for (int i = 0; i < queue.size(); ++i) {
        auto entity = queue.entityAt(i);
        if (entity->isAlive()) {
            return entity;
        }
    }

    return nullptr;
}

void BattleSystem::updateEntities() {
    std::vector<std::shared_ptr<Entity>> entities;
    while (!queue.isEmpty()) {
        auto entity = queue.popEntity();
        auto map = GameState::getInstance().getCurrentLevel().getMap();
        entity->update(*map);
        if (entity->isAlive())
            entities.push_back(entity);
    }

    for (const auto& e : entities) queue.addEntity(e);
}

void BattleSystem::readEntitiesFromFile(const std::string &pathToInitFile) {
    try {
        auto config = Config::getInstance(pathToInitFile);
        addEntityToList(config->createCharacter());
        addEntityToList(config->createEntity<Scarab>("Scarab"));
        addEntityToList(config->createEntity<Skeleton>("Skeleton"));
        addEntityToList(config->createEntity<Mummy>("Mummy"));
        addEntityToList(config->createEntity<Phantom>("Phantom"));
        addEntityToList(config->createEntity<SandGolem>("SandGolem"));
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
