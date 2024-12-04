#include "effects/Effect.hpp"

Effect::Effect(const std::string &name, int duration)
    : name(name), duration(duration)
{
}

int Effect::getDuration() const {
    return duration;
}

void Effect::setDuration(int duration) {

}

void Effect::reduceDuration() {
    std::max(0, --duration);
}

bool Effect::isExpired() const {
    return duration <= 0;
}

const std::string &Effect::getName() const {
    return name;
}
