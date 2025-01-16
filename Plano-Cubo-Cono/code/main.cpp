/**
    @author - Ignacio Tapia Marfil
*/

#include <SDL.h>
#include <iostream>
#include "Window.hpp"
#include "Scene.hpp"

using namespace OpenGLTapia;

int main(int , char*[])
{
    constexpr unsigned viewport_width = 1024;
    constexpr unsigned viewport_height = 576;

    Window window
    (
        "OpenGL example",
        Window::Position::CENTERED,
        Window::Position::CENTERED,
        viewport_width,
        viewport_height,
        { 3, 3 }
    );

    Scene scene(viewport_width, viewport_height);

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

        window.swap_buffers();

    } while (not exit);

    SDL_Quit();

    return 0;
}