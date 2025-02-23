#include "PriorityQueue.hpp"
#include "entities/Entity.hpp"
#include <random>

void PriorityQueue::addEntity(const std::shared_ptr<Entity> &entity) {
    // add small random number to cooldown to avoid collisions
    float cooldown = entity->getCooldown();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.00, 0.01);
    float random = dist(gen);
    cooldown += random;
    queue.push({ cooldown, entity });
}

void PriorityQueue::removeEntity(const std::shared_ptr<Entity> &entity) {
    std::priority_queue<QueueItem> newQueue;
    while (!queue.empty()) {
        auto item = queue.top();
        queue.pop();
        if (item.entity != entity) {
            newQueue.push(item);
        }
    }
    queue = newQueue;
}

std::shared_ptr<Entity> PriorityQueue::entityAt(int index) const {
    if (index < 0 || index >= queue.size()) return nullptr;

    std::priority_queue<QueueItem> tempQueue = queue;
    for (int i = 0; i < index; i++) {
        tempQueue.pop();
    }
    return tempQueue.top().entity;
}

void PriorityQueue::clear() {
    while (!queue.empty()) {
        queue.pop();
    }
}

std::shared_ptr<Entity> PriorityQueue::popEntity() {
    if (isEmpty()) return nullptr;
    auto item = queue.top();
    queue.pop();
    return item.entity;
}

