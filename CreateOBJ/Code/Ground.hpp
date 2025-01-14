#ifndef PLANE_HEADER
#define PLANE_HEADER

#include <vector>
#include <glad/glad.h>
#include <string>
#include <../../../libs/stb/include/stb_image.h>

namespace udit
{

    class Ground
    {
    private:

        GLuint vbo_ids[3];
        GLuint vao_id;
        GLuint numIndices;

        std::vector<GLfloat> generateCoordinates();
        std::vector<GLfloat> generateColors();
        std::vector<GLushort> generateIndices();

        GLuint loadHeightMap(const std::string& path, int& width, int& height);

        int         segments = 200;
        float       length_X = 10000.0f;
        float       length_Y = 10000.0f;

    public:

        Ground();
        ~Ground();

        void render();

    };
}

#endif

