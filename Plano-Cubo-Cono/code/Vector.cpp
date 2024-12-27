/**
   @author - Ignacio Tapia Marfil
*/


#include "Vector.hpp"

namespace SDLTapia
{
    template <size_t N>
    float Vector<N>::magnitude() const 
    {
        float sum = 0;

        for (const auto& comp : components) 
        {
            sum += comp * comp;
        }

        return std::sqrt(sum);
    }

    template <size_t N>
    Vector<N> Vector<N>::normalize() const 
    {
        float mag = magnitude();

        if (mag == 0) return *this;

        Vector result;

        for (size_t i = 0; i < N; ++i) 
        {
            result[i] = components[i] / mag;
        }

        return result;
    }

    template <size_t N>
    Vector<N> Vector<N>::operator+(const Vector& other) const 
    {
        Vector result;

        for (size_t i = 0; i < N; ++i) 
        {
            result[i] = components[i] + other[i];
        }

        return result;
    }

    template <size_t N>
    Vector<N> Vector<N>::operator-(const Vector& other) const 
    {
        Vector result;

        for (size_t i = 0; i < N; ++i) 
        {
            result[i] = components[i] - other[i];
        }

        return result;
    }

    template <size_t N>
    Vector<N> Vector<N>::operator/(float scalar) const 
    {
        Vector result;

        for (size_t i = 0; i < N; ++i) 
        {
            result[i] = components[i] / scalar;
        }

        return result;
    }

    template <size_t N>
    Vector<N> Vector<N>::operator*(float scalar) const 
    {
        Vector result;

        for (size_t i = 0; i < N; ++i) 
        {
            result[i] = components[i] * scalar;
        }

        return result;
    }

    template <size_t N>
    float Vector<N>::dot(const Vector& other) const 
    {
        float result = 0;
        for (size_t i = 0; i < N; ++i) 
        {
            result += components[i] * other[i];
        }

        return result;
    }

    template class Vector<2>;
    template class Vector<3>;
}