#pragma once

#include <psxgpu.h>

#include <Engine/Render/RenderContext.hpp>

class Sprite
{
public:
    Sprite() {};
    Sprite(const uint32_t* location);
    ~Sprite();

    void Draw(int x, int y, int w, int h, int z);

    static void SetContext(RenderContext* _ctx) { ctx = _ctx; }

public:
    TIM_IMAGE tim;

private:
    static RenderContext* ctx;
};