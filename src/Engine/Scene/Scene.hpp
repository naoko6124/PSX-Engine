#pragma once

#include <Engine/Scene/Entity.hpp>
#include <Engine/Sprite/Sprite.hpp>
#include <Engine/Structs/LinkedList.hpp>

class Scene
{
public:
    ~Scene()
    {
        entities.Loop(&ClearEntity);
    }

    void OnStart()
    {
        entities.Loop(&StartEntity);
    }

    void OnUpdate()
    {
        entities.Loop(&UpdateEntity);
    }

    void AddEntity(Entity* e)
    {
        entities.Add(e);
    }

private:
    static void StartEntity(Entity* e)
    {
        e->OnStart();
    }
    static void UpdateEntity(Entity* e)
    {
        e->OnUpdate();
    }
    static void ClearEntity(Entity* e)
    {
        delete e;
    }

private:
    LinkedList<Entity*> entities;
};