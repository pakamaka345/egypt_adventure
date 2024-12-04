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

    virtual void apply(Entity& target) = 0;
    virtual void onTick(Entity& target) = 0;
    virtual void remove(Entity& target) = 0;

    int getDuration() const;
    void setDuration(int duration);
    void reduceDuration();
    bool isExpired() const;

    const std::string& getName() const;
};