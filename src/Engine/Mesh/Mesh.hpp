#pragma once

#include <cstdint>
#include <cstdio>
#include <psxgpu.h>
#include <psxgte.h>
#include <inline_c.h>

#include <Engine/Render/RenderContext.hpp>

typedef struct
{
    short v0, v1, v2, v3;
} INDEX;

class Mesh
{
public:
    Mesh() {}
    Mesh(SVECTOR *_vertices, INDEX *_indices, SVECTOR *_normals, const int _faces, const uint32_t *texture, int _resolution);

    void Draw(SVECTOR rotation, VECTOR position);

    static void SetContext(RenderContext *_ctx) { ctx = _ctx; }

private:
private:
    static RenderContext *ctx;

    TIM_IMAGE tim;
    uint16_t texture_tpage;
    uint16_t texture_clut;
    int resolution;

    SVECTOR *vertices;
    INDEX *indices;
    SVECTOR *normals;
    int faces;

    int p;

    MATRIX light_mtx = {
        /* X,  Y,  Z */
        -2048, -2048, -2048,
        0, 0, 0,
        0, 0, 0};
};