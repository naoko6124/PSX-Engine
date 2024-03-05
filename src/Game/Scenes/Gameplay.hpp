#pragma once

#include <Engine/Scene/Scene.hpp>
#include <Game/Shared/Player/Player.hpp>

void Gameplay(Scene* scene)
{
    Player* player = new Player();
    scene->AddEntity(player);
}