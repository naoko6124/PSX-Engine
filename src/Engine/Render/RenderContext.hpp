#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <psxgpu.h>

#include <Engine/Render/RenderBuffer.hpp>

static constexpr size_t DEFAULT_OT_LENGTH     = 15;
static constexpr size_t DEFAULT_BUFFER_LENGTH = 8192;

class RenderContext {
private:
	RenderBuffer _buffers[2];
	std::uint8_t *_next_packet;
	int          _active_buffer;

	// These functions are simply shorthands for _buffers[_active_buffer] and
	// _buffers[_active_buffer ^ 1] respectively. They are only used internally.
	inline RenderBuffer &_draw_buffer(void) {
		return _buffers[_active_buffer];
	}
	inline RenderBuffer &_disp_buffer(void) {
		return _buffers[_active_buffer ^ 1];
	}

public:
	RenderContext(
		std::size_t ot_length     = DEFAULT_OT_LENGTH,
		std::size_t buffer_length = DEFAULT_BUFFER_LENGTH
	);
	void setup(int w, int h, int r, int g, int b);
	void flip(void);

	// This is a "factory function" that allocates a new primitive within the
	// currently active buffer. It is a template method, meaning T will get
	// replaced at compile time by the type of the primitive we are going to
	// allocate (and sizeof(T) will change accordingly!).
	template<typename T> inline T *new_primitive(int z = 0) {
		// Place the primitive after all previously allocated primitives, then
		// insert it into the OT and bump the allocation pointer.
		auto prim = reinterpret_cast<T *>(_next_packet);

		addPrim(_draw_buffer().ot_entry(z), prim);
		_next_packet += sizeof(T);

		// Make sure we haven't yet run out of space for future primitives.
		assert(_next_packet <= _draw_buffer().buffer_end());

		return prim;
	}

	void draw_sprite(P_TAG* sprt) {
		_draw_buffer().drawPrim(sprt);
	}

	void draw_mesh(POLY_FT4* mesh) {
		_draw_buffer().drawPrim(mesh);
	}

	// A simple helper for drawing text using PSn00bSDK's debug font API. Note
	// that FntSort() requires the debug font texture to be uploaded to VRAM
	// beforehand by calling FntLoad().
	inline void draw_text(int x, int y, int z, const char *text) {
		_next_packet = reinterpret_cast<uint8_t *>(
			FntSort(_draw_buffer().ot_entry(z), _next_packet, x, y, text)
		);

		assert(_next_packet <= _draw_buffer().buffer_end());
	}
};