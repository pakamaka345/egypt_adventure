#include "effects/EffectManager.hpp"
#include "effects/Effect.hpp"
#include "entities/Entity.hpp"

void EffectManager::addEffect(const std::shared_ptr<Effect> &effect, Entity &target) {
    activeEffects.push_back(effect);
    effect->apply(target);
}

void EffectManager::updateEffects(Entity &target) {
    for (auto it = activeEffects.begin(); it != activeEffects.end(); ) {
        (*it)->onTick(target);
        (*it)->reduceDuration();
        if ((*it)->isExpired()) {
            (*it)->remove(target);
            it = activeEffects.erase(it);
        } else {
            ++it;
        }
    }
}

void EffectManager::clearEffects(Entity& target) {
    for (auto& effect : activeEffects) {
        effect->remove(target);
    }
    activeEffects.clear();
}

std::vector<std::shared_ptr<Effect>> &EffectManager::getActiveEffects() {
    return activeEffects;
}