/**
   @author - Ignacio Tapia Marfil
*/

#include "Vector.hpp"
#pragma once

namespace SDLTapia
{
	class Point3D
	{
	private:

		float x, y, z;

	public:

		Point3D() { x = 0; y = 0; z = 0; };

		Point3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};


		float getX() const { return x; } void setX(float _x) { x = _x; }
		float getY() const { return y; } void setY(float _y) { y = _y; }
		float getZ() const { return z; } void setZ(float _z) { z = _z; }

		float& operator[](size_t);

		bool operator==(const Point3D&) const;

		Vector<3> operator- (const Point3D&) const;

		Point3D operator* (const float);
		Point3D operator/ (const float);

	};

}
