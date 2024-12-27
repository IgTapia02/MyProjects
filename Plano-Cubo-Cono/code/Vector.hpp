/**
   @author - Ignacio Tapia Marfil
*/

#include <array>
#include <initializer_list>
#include <cmath>
#pragma once

/**
    
    Class Vector
*/

namespace SDLTapia
{
	template <size_t N>

	class Vector
	{

	private:

		std::array <float, N> components;

	public:

		Vector() { components.fill(0); };
		
		Vector(std::initializer_list<float> values)
		{
			size_t i = 0;
			for (auto value : values)
			{
				if (i < N) 
				{
					components[i] = value;
					++i;
				}
			}
		}

		float& operator[](size_t index)				{ return components[index]; }
		const float& operator[](size_t index) const { return components[index]; }

		float magnitude() const;
		Vector normalize() const;

		Vector operator+ (const Vector&) const;
		Vector operator- (const Vector&) const;

		Vector operator/ (float) const;
		Vector operator* (float) const;

		float dot(const Vector&) const;
	};
}