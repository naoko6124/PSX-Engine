#include <Engine/Render/RenderContext.hpp>

RenderContext::RenderContext(std::size_t ot_length, std::size_t buffer_length)
: _buffers{
		RenderBuffer(ot_length, buffer_length),
		RenderBuffer(ot_length, buffer_length)
} {}

void RenderContext::setup(int w, int h, int r, int g, int b) {
	// Place the two framebuffers vertically in VRAM.
	_buffers[0].setup(0, 0, w, h, r, g, b);
	_buffers[1].setup(0, 0, w, h, r, g, b);

	// Initialize the first buffer and clear its OT so that it can be used for
	// drawing.
	_active_buffer = 0;
	_next_packet   = _draw_buffer().buffer_start();
	_draw_buffer().clear_ot();

	// Turn on the video output.
	SetDispMask(1);
}

void RenderContext::flip(void) {
	// Wait for the GPU to finish drawing, then wait for vblank in order to
	// prevent screen tearing.
	DrawSync(0);
	VSync(0);

	// Display the framebuffer the GPU has just finished drawing and start
	// rendering the display list that was filled up in the main loop.
	_disp_buffer().display();
	_draw_buffer().draw();

	// Switch over to the next buffer, clear it and reset the packet allocation
	// pointer.
	_active_buffer ^= 1;
	_next_packet    = _draw_buffer().buffer_start();
	_draw_buffer().clear_ot();
}