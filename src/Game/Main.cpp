#include <cstdint>
#include <cstdio>
#include <psxgpu.h>
#include <psxgte.h>
#include <inline_c.h>

#include <Engine/Core/Application.hpp>
#include <Game/Scenes/Gameplay.hpp>

int main()
{
    Application application;
    Scene scene;
    Gameplay(&scene);
    application.scene = &scene;
    application.Run();

    return 0;
}