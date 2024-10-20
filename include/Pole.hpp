#pragma once
#include "PoleType.hpp"
#include "Entity.hpp"
#include "Item.hpp"
#include <memory>


class Pole
{
private:
    std::unique_ptr<Entity> entity;
    std::unique_ptr<Item> item;
    PoleType::PoleType poleType;
    char symbol;

public:
    Pole(PoleType::PoleType poleType);
    ~Pole() = default;

    void setEntity(std::unique_ptr<Entity> entity);
    void setItem(std::unique_ptr<Item> item);

    std::unique_ptr<Entity> getEntity();
    std::unique_ptr<Item> getItem();

    PoleType::PoleType getPoleType();
    void setPoleType(PoleType::PoleType poleType);

    bool hasEntity();
    bool hasItem();

    void removeEntity();
    void removeItem();

    virtual char getSymbol();

    virtual bool isWalkable();

    virtual void draw();

private:
    virtual void setSymbol(PoleType::PoleType poleType);
};