/**
    @author - Ignacio Tapia Marfil
*/

#ifndef PLANE_HEADER
#define PLANE_HEADER

    #include <vector>
    #include <glad/glad.h>

    namespace OpenGLTapia
    {

        class Plane
        {
        private:

            GLuint vbo_ids[3];
            GLuint vao_id;
            GLuint numIndices;

            std::vector<GLfloat> GenerateCoordinates();
            std::vector<GLfloat> GenerateColors();
            std::vector<GLushort> GenerateIndices();

            int         segments = 2;
            float       length_X   = 8.0f;
            float       length_Y   = 8.0f;

        public:

            Plane();
            ~Plane();

            void Render();

        };
    }

#endif
