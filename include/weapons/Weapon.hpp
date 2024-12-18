#pragma once
#include <string>
#include <utility>
#include <vector>

class Bullet;
class Entity;

/**
 * \brief Weapon class. In this implementation is a only a one type of weapon.
 * Can be changed to be a base class for different types of weapons.
 */
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
    void shootWithMiss();


    int getAmmo();
    int getMagazineSize();
    std::vector<Bullet>& getMagazine();
    std::string& getName();
};