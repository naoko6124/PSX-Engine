#pragma once

#include <Engine/Render/RenderContext.hpp>

#include <Engine/Scene/Scene.hpp>

class Application
{
public:
    Application();
    ~Application();

    void Run();

private:
    void Loop();

public:
    Scene* scene;

private:
	RenderContext ctx;
};