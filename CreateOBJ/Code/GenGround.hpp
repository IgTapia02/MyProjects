#pragma once


#ifndef PLANE_HEADER
#define PLANE_HEADER

#include <vector>
#include <glad/glad.h>

namespace Udit
{

    class GenGround
    {
    private:

        GLuint vbo_ids[3];
        GLuint vao_id;
        GLuint numIndices;

        std::vector<GLfloat> generateCoordinates();
        std::vector<GLfloat> generateColors();
        std::vector<GLushort> generateIndices();

        int         segments = 2;
        float       length_X = 8.0f;
        float       length_Y = 8.0f;

    public:

        Plane();
        ~Plane();

        void render();

    };
}

#endif
