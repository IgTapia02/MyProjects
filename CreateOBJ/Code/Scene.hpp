
// Este código es de dominio público
// angel.rodriguez@udit.es

#ifndef SCENE_HEADER
#define SCENE_HEADER

#include <SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "Camera.hpp"
#include "Mesh.hpp"
#include "Ground.hpp"

namespace udit
{

    using glm::vec3;

    class Scene
    {
    private:

        enum
        {
            COORDINATES_VBO,
            COLORS_VBO,
            INDICES_EBO,
            VBO_COUNT
        };

        static const std::string   vertex_shader_code;
        static const std::string fragment_shader_code;

        GLuint  vbo_ids[VBO_COUNT];
        GLuint  vao_id;

        GLsizei number_of_indices;

        GLint   model_view_matrix_id;
        GLint   projection_matrix_id;

        const std::string& filePath;

        Mesh mesh;
        Ground ground;

        Camera camera;

    public:

        Scene(int width, int height, const std::string& _filePath);
        ~Scene();

        void   update();
        void   render();
        void   resize(int width, int height);

    private:

        GLuint compile_shaders();
        void   show_compilation_error(GLuint  shader_id);
        void   show_linkage_error(GLuint program_id);


        void processInput(const Uint8* keyboardState, float deltaTime);
        void processMouseMotion(int xrel, int yrel);
    };

}

#endif
