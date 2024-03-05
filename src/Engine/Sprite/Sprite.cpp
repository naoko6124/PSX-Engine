#include <Engine/Sprite/Sprite.hpp>

RenderContext* Sprite::ctx = nullptr;

Sprite::Sprite(const uint32_t *location)
{
	GetTimInfo(location, &tim);
	if (tim.mode & 0x8)
		LoadImage(tim.crect, tim.caddr); /* Upload CLUT if present */
	LoadImage(tim.prect, tim.paddr);
}

Sprite::~Sprite()
{
}

void Sprite::Draw(int x, int y, int w, int h, int z)
{
	auto sprt = ctx->new_primitive<SPRT>(z);

	setSprt(sprt);
	setXY0(sprt, x, y);
	setRGB0(sprt, 255, 255, 255);
	setUV0(sprt, 0, 1);
	setWH(sprt, w, h);

	setClut(sprt, tim.crect->x, tim.crect->y);
	ctx->draw_sprite((P_TAG *)sprt);

	auto tpri = ctx->new_primitive<DR_TPAGE>(z);
	setDrawTPage(tpri, 0, 0,
				 getTPage(0, 0, tim.prect->x, tim.prect->y));
	ctx->draw_sprite((P_TAG *)tpri);
}