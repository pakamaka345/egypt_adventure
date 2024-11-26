#pragma once
#include <string>
#include <utility>
#include <vector>
#include "items/Bullet.hpp"
#include "entities/Entity.hpp"

class Entity;

class Weapon
{
protected:
    std::string name;
    std::vector<Bullet> magazine;
    int magazineSize;

public:
    Weapon(std::string name, int magazineSize);

    void addBullet(Bullet& bullet);
    void shoot(Entity& target);


    int getAmmo() { return int(magazine.size()); }
    [[nodiscard]] int getMagazineSize() const { return magazineSize; }
    std::vector<Bullet>& getMagazine() { return magazine; }
    std::string& getName() { return name; }
};