#pragma once

struct Vector2
{
	float x, y;
};

struct Vector3
{
	float x, y, z;

	Vector3 operator-(const Vector3& vec)
	{

		return { x - vec.x, y - vec.y, z - vec.z };

	}

};

struct Vector4
{
	float x, y, z, w;
};