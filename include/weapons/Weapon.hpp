#pragma once
#include <string>
#include <utility>

class Weapon
{
private:
    std::string name;
    std::pair<float, float> physicalDamage;
    std::pair<float, float> magicalDamage;

public:
    Weapon(std::string& name, std::pair<float, float>& physicalDamage, std::pair<float, float>& magicalDamage);

    std::pair<float, float>& getPhysicalDamage();
    std::pair<float, float>& getMagicalDamage();
    std::string& getName();

    void increasePhysicalDamage(float value);
    void increaseMagicalDamage(float value);
};