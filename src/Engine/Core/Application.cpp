#include <Engine/Core/Application.hpp>

#include <psxgpu.h>

#include <Engine/Core/Debug.hpp>
#include <Engine/Sprite/Sprite.hpp>
#include <Engine/Mesh/Mesh.hpp>
#include <Engine/Input/Input.hpp>

#define SCREEN_XRES 320
#define SCREEN_YRES 240
#define CENTERX SCREEN_XRES >> 1
#define CENTERY SCREEN_YRES >> 1

Application::Application()
{
	ResetGraph(0);
	FntLoad(960, 0);

	ctx.setup(320, 240, 0, 0, 0);

	MATRIX color_mtx = {
		ONE * 3 / 4, 0, 0, /* Red   */
		ONE * 3 / 4, 0, 0, /* Green */
		ONE * 3 / 4, 0, 0  /* Blue  */
	};
	
	InitGeom();
	gte_SetGeomOffset(CENTERX, CENTERY);
	gte_SetGeomScreen(CENTERX);
	gte_SetBackColor(63, 63, 63);
	gte_SetColorMatrix(&color_mtx);
}

Application::~Application()
{
}

void Application::Run()
{
	Input::Init();
	Sprite::SetContext(&ctx);
	Mesh::SetContext(&ctx);
	Debug::SetContext(&ctx);

	scene->OnStart();

	while (true)
	{
		scene->OnUpdate();

		ctx.flip();
	}
}