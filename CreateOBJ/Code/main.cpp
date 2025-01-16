/**
    @author - Ignacio Tapia Marfil
*/

#include <fstream>
#include "Scene.hpp"
#include "Window.hpp"
#include "MeshSaveLoad.hpp"
#include <glm/glm.hpp>



using OpenGlTapia::Scene;
using OpenGLTapia::Window;
using OpenGlTapia::Mesh;
using OpenGlTapia::MeshSaveLoad;

/// Funcion para coger y transformar todos las mesh y crear el .obj escenario que vamos a instanciar despues.
void CreateMesh();


const std::string& filePath = "../../../assets/output.obj"; ///< Path donde guardaremos ese .obj.

int main(int, char* [])
{
    constexpr unsigned viewport_width  = 1920;
    constexpr unsigned viewport_height = 1080;

    Window window
    (
        "OpenGL example",
        Window::Position::CENTERED,
        Window::Position::CENTERED,
        viewport_width,
        viewport_height,
        { 3, 3 }
    );

    CreateMesh();

    Scene scene(viewport_width, viewport_height, filePath);

    bool exit = false;

    do
    {

        SDL_Event event;

        while (SDL_PollEvent(&event) > 0)
        {
            if (event.type == SDL_QUIT)
            {
                exit = true;
            }
        }

        scene.Update();

        scene.Render();

        window.SwapBuffers();

    } while (not exit);

    SDL_Quit();

    return 0;
}

void CreateMesh()
{
    std::vector<Mesh> meshes;

    meshes.emplace_back(Mesh("../../../assets/Mesa.obj"));

    meshes.emplace_back(Mesh("../../../assets/Botella.obj"));

    meshes.emplace_back(Mesh("../../../assets/SM_BotecChuchurrio.fbx"));


    std::vector<glm::mat4> transforms;

    glm::vec3 position1(0.f, 0.f, 0.f);

    glm::vec3 rotation1(0.f, 1.0f, 0.f);

    float angle1_1 = 90.f;

    glm::vec3 scale1(6.0f, 5.0f, 3.0f);

    glm::mat4 transformMesh1 = 
        glm::translate(glm::mat4(1.0f), position1) *
        glm::rotate(glm::mat4(1.0f), glm::radians(angle1_1), rotation1) *
        glm::scale(glm::mat4(3.0f), scale1);

    transforms.push_back(transformMesh1);

    glm::vec3 position2(30.0f, 74.0f, 0.0f);

    glm::vec3 scale2(1.0f, 1.0f, 1.0f);

    glm::mat4 transformMesh2 = 
        glm::scale(glm::mat4(1.0f), scale2) *
        glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
        glm::translate(glm::mat4(1.0f), position2);

    transforms.push_back(transformMesh2);

    glm::vec3 position3(20.f, -40.f, 140.f);

    glm::vec3 rotation3_1(1.f, 0.f, 0.f);
    glm::vec3 rotation3_2(0.f, 0.f, 1.f);

    float angle3_1 = -90.f;

    float angle3_2 = -90.f;

    glm::vec3 scale3(1.f, 2.f, 2.f);

    glm::mat4 transformMesh3 = 
        glm::translate(glm::mat4(1.0f), position3) *
        glm::rotate(glm::mat4(1.0f), glm::radians(angle3_1), rotation3_1) *
        glm::rotate(glm::mat4(1.0f), glm::radians(angle3_2), rotation3_2) *
        glm::scale(glm::mat4(3.0f), scale3);

    transforms.push_back(transformMesh3);

    MeshSaveLoad::SaveAsObj(filePath, meshes, transforms);

}