#pragma once

#include <Engine/Core/Debug.hpp>
#include <Engine/Scene/Entity.hpp>
#include <Engine/Input/Input.hpp>
#include <Engine/Mesh/Mesh.hpp>

extern const uint32_t girl_tim[];
extern const uint32_t tim_texture[];

class Player : public Entity
{
public:
	void OnStart() override
	{
		cube_verts[0] = {-100, -100, -100, 0};
		cube_verts[1] = {100, -100, -100, 0};
		cube_verts[2] = {-100, 100, -100, 0};
		cube_verts[3] = {100, 100, -100, 0};
		cube_verts[4] = {100, -100, 100, 0};
		cube_verts[5] = {-100, -100, 100, 0};
		cube_verts[6] = {100, 100, 100, 0};
		cube_verts[7] = {-100, 100, 100, 0};

		cube_norms[0] = {0, 0, -ONE, 0};
		cube_norms[1] = {0, 0, ONE, 0};
		cube_norms[2] = {0, -ONE, 0, 0};
		cube_norms[3] = {0, ONE, 0, 0};
		cube_norms[4] = {-ONE, 0, 0, 0};
		cube_norms[5] = {ONE, 0, 0, 0};

		cube_indices[0] = {0, 1, 2, 3};
		cube_indices[1] = {4, 5, 6, 7};
		cube_indices[2] = {5, 4, 0, 1};
		cube_indices[3] = {6, 7, 3, 2};
		cube_indices[4] = {0, 2, 5, 7};
		cube_indices[5] = {3, 1, 6, 4};

		cube = Mesh(cube_verts, cube_indices, cube_norms, 6, tim_texture, 128);

		girl = Sprite(girl_tim);
	}
	
	void OnUpdate() override
	{
		cube.Draw(rot, pos);
		girl.Draw(x, y, 64, 64, 1);

		rot.vx += 16;
		rot.vz += 16;

		if (Input::GetKey(Keys::Up))
			y -= 1;
		if (Input::GetKey(Keys::Right))
			x += 1;
		if (Input::GetKey(Keys::Down))
			y += 1;
		if (Input::GetKey(Keys::Left))
			x -= 1;

		if (Input::GetKey(Keys::Triangle))
			pos.vy -= 4;
		if (Input::GetKey(Keys::Circle))
			pos.vx += 4;
		if (Input::GetKey(Keys::Cross))
			pos.vy += 4;
		if (Input::GetKey(Keys::Square))
			pos.vx -= 4;
	}

private:
	SVECTOR cube_verts[8];

	SVECTOR cube_norms[6];

	INDEX cube_indices[6];

	Sprite girl;
	int x = 0, y = 0;

	Mesh cube;
	SVECTOR rot = {0};
	VECTOR pos = {0, 0, 400};
};