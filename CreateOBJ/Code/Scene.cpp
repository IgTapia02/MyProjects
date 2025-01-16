/**
    @author - Ignacio Tapia Marfil
*/

#include "Scene.hpp"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


using namespace std;
using namespace glm;

namespace OpenGlTapia
{

    const string Scene::vertex_shader_code =

        "#version 330\n"
        ""
        "uniform mat4 model_view_matrix;"
        "uniform mat4 projection_matrix;"
        ""
        "layout (location = 0) in vec3 vertex_coordinates;"
        "layout (location = 1) in vec3 vertex_color;"
        ""
        "out vec3 front_color;"
        ""
        "void main()"
        "{"
        "   gl_Position = projection_matrix * model_view_matrix * vec4(vertex_coordinates, 1.0);"
        "   front_color = vertex_color;"
        "}";

    const string Scene::fragment_shader_code =

        "#version 330\n"
        ""
        "in  vec3    front_color;"
        "out vec4 fragment_color;"
        ""
        "void main()"
        "{"
        "    fragment_color = vec4(front_color, 1.0);"
        "}";

    Scene::Scene(int width, int height, const std::string& _filePath)
        : filePath(_filePath),
        mesh(_filePath),
        camera(glm::vec3(0.0f, 600.0f, 0.f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f)
    {

        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glClearColor(.1f, .1f, .1f, 1.f);

        GLuint program_id = CompileShaders();

        glUseProgram(program_id);

        model_view_matrix_id = glGetUniformLocation(program_id, "model_view_matrix");
        projection_matrix_id = glGetUniformLocation(program_id, "projection_matrix");

        Resize(width, height);
    }

    Scene::~Scene()
    {
        glDeleteVertexArrays(1, &vao_id);
        glDeleteBuffers(VBO_COUNT, vbo_ids);
    }

    void Scene::Update()
    {
        const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

        ProcessInput(keyboardState, 1.f);

        int xrel, yrel;
        SDL_GetRelativeMouseState(&xrel, &yrel);
        ProcessMouseMotion(xrel, yrel);

    }

    void Scene::Render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model_view_matrix_1 = camera.GetViewMatrix();

        model_view_matrix_1 = glm::translate(model_view_matrix_1, glm::vec3(-2000.f, 0.f, -2000.f));

        glUniformMatrix4fv(model_view_matrix_id, 1, GL_FALSE, glm::value_ptr(model_view_matrix_1));
        ground.Render();

        glm::mat4 model_view_matrix_2 = camera.GetViewMatrix();

        model_view_matrix_2 = glm::translate(model_view_matrix_2, glm::vec3(0.f, 310.f, 0.f));

        model_view_matrix_2 = glm::scale(model_view_matrix_2, glm::vec3(3.f, 3.f, 3.f));

        mesh.Render(model_view_matrix_id, model_view_matrix_2);

        glUniformMatrix4fv(model_view_matrix_id, 1, GL_FALSE, glm::value_ptr(model_view_matrix_2));
    }

    void Scene::Resize(int width, int height)
    {
        glm::mat4 projection_matrix = glm::perspective(20.f, GLfloat(500) / 500, 1.f, 5000.f);

        glUniformMatrix4fv(projection_matrix_id, 1, GL_FALSE, glm::value_ptr(projection_matrix));

        glViewport(0, 0, (float)width, (float)height);
    }

    GLuint Scene::CompileShaders()
    {
        GLint succeeded = GL_FALSE;

        GLuint   vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

        const char* vertex_shaders_code[] = { vertex_shader_code.c_str() };
        const char* fragment_shaders_code[] = { fragment_shader_code.c_str() };
        const GLint    vertex_shaders_size[] = { (GLint)vertex_shader_code.size() };
        const GLint  fragment_shaders_size[] = { (GLint)fragment_shader_code.size() };

        glShaderSource(vertex_shader_id, 1, vertex_shaders_code, vertex_shaders_size);
        glShaderSource(fragment_shader_id, 1, fragment_shaders_code, fragment_shaders_size);

        glCompileShader(vertex_shader_id);
        glCompileShader(fragment_shader_id);

        glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &succeeded);
        if (!succeeded) ShowCompilationError(vertex_shader_id);

        glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &succeeded);
        if (!succeeded) ShowCompilationError(fragment_shader_id);

        GLuint program_id = glCreateProgram();

        glAttachShader(program_id, vertex_shader_id);
        glAttachShader(program_id, fragment_shader_id);

        glLinkProgram(program_id);

        glGetProgramiv(program_id, GL_LINK_STATUS, &succeeded);
        if (!succeeded) ShowLinkageError(program_id);

        glDeleteShader(vertex_shader_id);
        glDeleteShader(fragment_shader_id);

        return (program_id);
    }

    void Scene::ShowCompilationError(GLuint shader_id)
    {
        string info_log;
        GLint  info_log_length;

        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

        info_log.resize(info_log_length);

        glGetShaderInfoLog(shader_id, info_log_length, NULL, &info_log.front());

        cerr << info_log.c_str() << endl;

        assert(false);
    }

    void Scene::ShowLinkageError(GLuint program_id)
    {
        string info_log;
        GLint  info_log_length;

        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);

        info_log.resize(info_log_length);

        glGetProgramInfoLog(program_id, info_log_length, NULL, &info_log.front());

        cerr << info_log.c_str() << endl;

        assert(false);
    }

    void Scene::ProcessInput(const Uint8* keyboardState, float deltaTime)
    {
        float cameraSpeed = 2.5f * deltaTime;

        if (keyboardState[SDL_SCANCODE_W]) camera.ProcessKeyboard(FORWARD, deltaTime);
        if (keyboardState[SDL_SCANCODE_S]) camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (keyboardState[SDL_SCANCODE_A]) camera.ProcessKeyboard(LEFT, deltaTime);
        if (keyboardState[SDL_SCANCODE_D]) camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    void Scene :: ProcessMouseMotion(int xrel, int yrel) 
    {
        float sensitivity = 2.f;
        camera.ProcessMouseMovement(xrel * sensitivity, yrel * sensitivity, true);
    }

}
