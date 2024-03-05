#pragma once

#include <Engine/Structs/LinkedList.hpp>

class Entity
{
public:
    virtual void OnStart() = 0;
    virtual void OnUpdate() = 0;
};