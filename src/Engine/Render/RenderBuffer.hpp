#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <psxgpu.h>

class RenderBuffer {
private:
	DISPENV _disp_env;
	DRAWENV _draw_env;

	std::uint32_t *_ot;
	std::uint8_t  *_buffer;
	std::size_t   _ot_length, _buffer_length;

public:
	RenderBuffer(std::size_t ot_length, std::size_t buffer_length);
	~RenderBuffer(void);
	void setup(int x, int y, int w, int h, int r, int g, int b);

	inline uint8_t *buffer_start(void) const {
		return _buffer;
	}
	inline uint8_t *buffer_end(void) const {
		return &_buffer[_buffer_length];
	}
	inline uint32_t *ot_entry(int z) const {
		//assert((z >= 0) && (z < _ot_length));
		return &_ot[z];
	}

	inline void clear_ot(void) {
		ClearOTagR(_ot, _ot_length);
	}
	inline void draw(void) {
		DrawOTagEnv(&_ot[_ot_length - 1], &_draw_env);
	}
	inline void display(void) const {
		PutDispEnv(&_disp_env);
	}
	void drawPrim(P_TAG* sprt) const {
		addPrim(_ot, sprt);
	}
	void drawPrim(POLY_FT4* mesh) const {
		addPrim(_ot, mesh);
	}
};