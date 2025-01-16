/**
    @author - Ignacio Tapia Marfil
*/

#ifndef CONE_HEADER
#define CONE_HEADER


    #include <vector>
    #include <glad/glad.h>

    namespace OpenGLTapia
    {

        class Cone
        {

        private:

            GLuint vbo_ids[3];
            GLuint vao_id;
            GLuint numIndices;

            std::vector<GLfloat> GenerateCoordinates();
            std::vector<GLfloat> GenerateColors();
            std::vector<GLubyte> GenerateIndices();

            int         segments = 36;
            float       radius   = 1.0f;
            float       height   = 2.0f;

        public:

            Cone();
            ~Cone();

            void Render();

        };
    }

#endif