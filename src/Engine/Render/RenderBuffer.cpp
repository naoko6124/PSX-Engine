#include <Engine/Render/RenderBuffer.hpp>

RenderBuffer::RenderBuffer(std::size_t ot_length, std::size_t buffer_length)
: _ot_length(ot_length), _buffer_length(buffer_length) {
	// Initializing the OT in a constructor is unsafe, since ClearOTagR()
	// requires DMA to be enabled and may fail if called before ResetGraph() or
	// ResetCallback() (which can easily happen as constructors can run before
	// main()). Thus, this constructor is only going to allocate the buffers and
	// clearing is deferred to RenderContext::setup().
	_ot     = new uint32_t[ot_length];
	_buffer = new uint8_t[buffer_length];

	assert(_ot && _buffer);

	//std::printf("Allocated buffer, ot=0x%08x, buffer=0x%08x\n", ot, buffer);
}

RenderBuffer::~RenderBuffer(void) {
	delete[] _ot;
	delete[] _buffer;

	//std::printf("Freed buffer, ot=0x%08x, buffer=0x%08x\n", ot, buffer);
}

void RenderBuffer::setup(int x, int y, int w, int h, int r, int g, int b) {
	// Set the framebuffer's VRAM coordinates.
	SetDefDrawEnv(&_draw_env, x, y, w, h);
	SetDefDispEnv(&_disp_env, x, y, w, h);

	// Set the default background color and enable auto-clearing.
	setRGB0(&_draw_env, r, g, b);
	_draw_env.isbg = 1;
}