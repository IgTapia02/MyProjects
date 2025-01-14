#include <fstream>
#include "Scene.hpp"
#include "Window.hpp"
#include "MeshSaveLoad.hpp"
#include <glm/glm.hpp>



using udit::Scene;
using udit::Window;
void createMesh();

const std::string& filePath = "../../../assets/output.obj";

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

    createMesh();

    Scene scene(viewport_width, viewport_height, filePath);

    bool exit = false;

    do
    {
        // Se procesan los eventos acumulados:

        SDL_Event event;

        while (SDL_PollEvent(&event) > 0)
        {
            if (event.type == SDL_QUIT)
            {
                exit = true;
            }
        }

        // Se actualiza la escena:

        scene.update();

        // Se redibuja la escena:

        scene.render();

        // Se actualiza el contenido de la ventana:

        window.swap_buffers();

    } while (not exit);

    SDL_Quit();

    return 0;
}

void createMesh()
{
    std::vector<Mesh> meshes;

    meshes.emplace_back(Mesh("../../../assets/Mesa.obj"));

    meshes.emplace_back(Mesh("../../../assets/Botella.obj"));

    std::vector<glm::mat4> transforms;

    // Malla 1: trasladar y rotar
    glm::vec3 position1(0.f, 0.f, 0.f);

    glm::vec3 rotation1(0.f, 1.0f, 0.f);

    float angle = 90.f;

    glm::vec3 scale1(6.0f, 5.0f, 3.0f);

    glm::mat4 transformMesh1 = glm::translate(glm::mat4(1.0f), position1) *
        glm::rotate(glm::mat4(1.0f), glm::radians(angle), rotation1) *
        glm::scale(glm::mat4(3.0f), scale1);

    transforms.push_back(transformMesh1); // Agregar la transformación a la malla 1

    // Malla 2: escalar, rotar y trasladar
    glm::vec3 position2(30.0f, 74.0f, 0.0f);

    glm::vec3 scale2(1.0f, 1.0f, 1.0f);

    glm::mat4 transformMesh2 = glm::scale(glm::mat4(1.0f), scale2) *
        glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
        glm::translate(glm::mat4(1.0f), position2);

    transforms.push_back(transformMesh2); // Agregar la transformación a la malla 2

    MeshSaveLoad::saveAsObj(filePath, meshes, transforms);

}