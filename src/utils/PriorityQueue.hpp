#pragma once
#include <queue>
#include <memory>

class Entity;

class PriorityQueue {
private:
    struct QueueItem {
        float cooldown;
        std::shared_ptr<Entity> entity;

        bool operator<(const QueueItem& other) const {
            return cooldown > other.cooldown;
        }
    };

    std::priority_queue<QueueItem> queue;

public:
    PriorityQueue() = default;
    ~PriorityQueue() = default;

    void addEntity(const std::shared_ptr<Entity>& entity);
    void removeEntity(const std::shared_ptr<Entity>& entity);
    std::shared_ptr<Entity> entityAt(int index) const;
    void clear();

    std::shared_ptr<Entity> popEntity();

    bool isEmpty() const { return queue.empty(); }
    size_t size() const { return queue.size(); }
};