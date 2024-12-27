
// Este c�digo es de dominio p�blico
// angel.rodriguez@udit.es

#pragma once

#include "Shape.hpp"
#include <string>

namespace SDLTapia
{

    class Scene
    {
    private:

        static const std::string   vertex_shader_code;
        static const std::string fragment_shader_code;

        GLint  model_view_matrix_id;
        GLint  projection_matrix_id;

        Shape shape;
        float  angle;

    public:

        Scene(unsigned width, unsigned height);

        void   update();
        void   render();
        void   resize(unsigned width, unsigned height);

    private:

        GLuint compile_shaders();
        void   show_compilation_error(GLuint  shader_id);
        void   show_linkage_error(GLuint program_id);

    };

}
