/**
   @author - Ignacio Tapia Marfil
*/

#include <glad/glad.h>
#include "Point3D.hpp"
#include <vector>

#pragma once

namespace SDLTapia
{
    class Shape
    {
    private:

        enum
        {
            COORDINATES_VBO,
            COLORS_VBO,
            INDICES_EBO,
            VBO_COUNT
        };

        std::vector<GLfloat> coordinates;
        std::vector<GLfloat> colors;
        std::vector<GLfloat> indices;

        GLuint vbo_ids[VBO_COUNT];      // Ids de los VBOs que se usan
        GLuint vao_id;                  // Id del VAO del cubo

    public:

        Shape();
        Shape(Point3D startPoint, GLfloat, GLfloat);
        ~Shape();

        void genCoordinates(Point3D, GLfloat);

        void render();
    };
}