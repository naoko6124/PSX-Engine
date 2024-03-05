#pragma once

#include <Engine/Render/RenderContext.hpp>

class Debug
{
public:
    static void Log(int x, int y, int z, const char* message)
    {
        ctx->draw_text(x, y, z, message);
    }

    static void SetContext(RenderContext* _ctx) { ctx = _ctx; }

private:
    static RenderContext* ctx;
};