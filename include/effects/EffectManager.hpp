#pragma once
#include <vector>
#include <memory>

class Entity;
class Effect;

/**
 * \brief Manages all effects in the game.
 */
class EffectManager
{
private:
    std::vector<std::shared_ptr<Effect>> activeEffects;

public:
    void addEffect(const std::shared_ptr<Effect>& effect, Entity& target);
    void updateEffects(Entity& target);

    void clearEffects(Entity& target);
    std::vector<std::shared_ptr<Effect>>& getActiveEffects();
};