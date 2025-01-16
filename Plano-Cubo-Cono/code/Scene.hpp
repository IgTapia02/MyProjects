/**
    @author - Ignacio Tapia Marfil
*/


#ifndef SCENE_HEADER
#define SCENE_HEADER

    #include "Cube.hpp"
    #include "Plane.hpp"
    #include "Cone.hpp"
    #include <string>

    namespace OpenGLTapia
    {

        class Scene
        {
        private:

            static const std::string   vertex_shader_code;
            static const std::string fragment_shader_code;

            GLint  model_view_matrix_id;
            GLint  projection_matrix_id;

            Plane  plane;
            Cube   cube;
            Cone   cone;
            float  angle;

        public:

            Scene(unsigned width, unsigned height);

            void   Update();
            void   Render();
            void   Resize(unsigned width, unsigned height);

        private:

            GLuint CompileShaders();
            void   ShowCompilationError(GLuint  shader_id);
            void   ShowLinkageError(GLuint program_id);

        };

    }

#endif

