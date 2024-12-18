#pragma once
#include <iostream>

class Interface {
public:
    Interface() = default;
    virtual void draw() const = 0;
};