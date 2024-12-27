/**
   @author - Ignacio Tapia Marfil
*/


#include "Point3D.hpp"


namespace SDLTapia 
{
    
    float& Point3D::operator[] (size_t index)
    {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
    }

    bool Point3D::operator==     (const Point3D& other) const
    {
        return this->x == other.x && this->y == other.y && this->z == other.z;
    }

    Vector<3> Point3D::operator- (const Point3D& other) const
    {
        return Vector<3> {this->x - other.x, this->y - other.y, this->z - other.z};
    }

    Point3D Point3D::operator*   (const float scalar)
    {
        return Point3D (x * scalar, y * scalar, z * scalar);
    }

    Point3D Point3D::operator/   (const float scalar)
    {
        return Point3D (x / scalar, y / scalar, z / scalar);
    }
}