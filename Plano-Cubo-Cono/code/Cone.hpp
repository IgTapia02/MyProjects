
#ifndef CONE_HEADER
#define CONE_HEADER


    #include <vector>
    #include <glad/glad.h>

    namespace SDLTapia
    {

        class Cone
        {

        private:

            GLuint vbo_ids[3];
            GLuint vao_id;
            GLuint numIndices;

            std::vector<GLfloat> generateCoordinates();
            std::vector<GLfloat> generateColors();
            std::vector<GLubyte> generateIndices();

            int         segments = 36;
            float       radius   = 1.0f;
            float       height   = 2.0f;

        public:

            Cone();
            ~Cone();

            void render();

        };
    }

#endif