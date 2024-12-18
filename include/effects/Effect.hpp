#pragma once
#include <string>

class Entity;

/**
 * Abstract class representing an effect that can be applied to an entity.
 * Different from an amulet`s effect, this effect is temporary and has a duration.
 */
class Effect
{
protected:
    std::string name;
    int duration;

public:
    Effect(const std::string& name, int duration);
    virtual ~Effect() = default;

    /**
     * @brief Applies when the effect is created.
     * @param target
     */
    virtual void apply(Entity& target) = 0;

    /**
     * @brief Updates the effect every tick(turn).
     * @param target
     */
    virtual void onTick(Entity& target) = 0;

    /**
     * @brief Does something when the effect is removed.
     * @param target
     */
    virtual void remove(Entity& target) = 0;

    int getDuration() const;
    void setDuration(int duration);
    void reduceDuration();
    bool isExpired() const;

    const std::string& getName() const;
};