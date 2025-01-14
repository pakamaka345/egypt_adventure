#pragma once
#include <string>
#include <vector>
#include <memory>

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
    std::vector<std::shared_ptr<Bullet>> magazine;
    int magazineSize;

public:
    Weapon(std::string name, int magazineSize);

    void addBullet(Bullet& bullet);
    void shoot();

    int getAmmo();
    int getMagazineSize() const;
    std::vector<std::shared_ptr<Bullet>>& getMagazine();
    std::string& getName();
};