#include <Engine/Mesh/Mesh.hpp>

#include <Engine/Core/Debug.hpp>

RenderContext *Mesh::ctx = nullptr;

Mesh::Mesh(SVECTOR *_vertices, INDEX *_indices, SVECTOR *_normals, const int _faces, const uint32_t *texture, int _resolution)
{
    vertices = _vertices;
    indices = _indices;
    normals = _normals;
    faces = _faces;
    resolution = _resolution;

    GetTimInfo(texture, &tim);
    if (tim.mode & 0x8)
        LoadImage(tim.crect, tim.caddr);
    LoadImage(tim.prect, tim.paddr);

    texture_tpage = getTPage(tim.mode, 1, tim.prect->x, tim.prect->y);
    texture_clut = getClut(tim.crect->x, tim.crect->y);
}

void Mesh::Draw(SVECTOR rotation, VECTOR position)
{
    POLY_FT4 *pol4;
    MATRIX mtx, lmtx;

    RotMatrix(&rotation, &mtx);
    TransMatrix(&mtx, &position);

    MulMatrix0(&light_mtx, &mtx, &lmtx);

    gte_SetRotMatrix(&mtx);
    gte_SetTransMatrix(&mtx);

    gte_SetLightMatrix(&lmtx);

    for (int i = 0; i < faces; i++)
    {
        gte_ldv3(
            &vertices[indices[i].v0],
            &vertices[indices[i].v1],
            &vertices[indices[i].v2]);

        gte_rtpt();
        gte_nclip();
        gte_stopz(&p);

        if (p < 0)
            continue;

        gte_avsz4();
        gte_stotz(&p);

        if ((p >> 2) > 256)
            continue;

        pol4 = ctx->new_primitive<POLY_FT4>(p);

        setPolyFT4(pol4);

        gte_stsxy0(&pol4->x0);
        gte_stsxy1(&pol4->x1);
        gte_stsxy2(&pol4->x2);

        gte_ldv0(&vertices[indices[i].v3]);
        gte_rtps();
        gte_stsxy(&pol4->x3);

        gte_ldrgb(&pol4->r0);
        gte_ldv0(&normals[i]);
        gte_ncs();
        gte_strgb(&pol4->r0);

        setUVWH(pol4, 0, 1, resolution, resolution);
        pol4->tpage = texture_tpage;
        pol4->clut = texture_clut;

        ctx->draw_mesh(pol4);
    }
}