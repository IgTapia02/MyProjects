
#include "Plane.hpp"
#include <iostream>

namespace SDLTapia 
{

    std::vector<GLfloat> Plane::generateCoordinates()
    {
        std::vector<GLfloat> coordinates;

        float x = 0.f;
        float y = 0.f;

        for (int i = 0; i <= segments; ++i)
        {
            for (int j = 0; j <= segments; ++j)
            {
                coordinates.push_back(x);
                coordinates.push_back(y);
                coordinates.push_back(0.f);

                x += length_X / segments;
            }

            x = 0.f;
            y += length_Y / segments;
        }

        return coordinates;
    }

    std::vector<GLfloat> Plane::generateColors()
    {
        std::vector<GLfloat> colors;

        // Alternar colores entre rojo, verde y azul
        for (int i = 0; i <= segments; ++i)
        {
            for (int j = 0; j <= segments; ++j)
            {
                int color_index = (i * (segments + 1) + j) % 3; // Determina el color basado en el índice del vértice
                if (color_index == 0) // Rojo
                {
                    colors.push_back(1.0f); // R
                    colors.push_back(0.0f); // G
                    colors.push_back(1.0f); // B
                }
                else if (color_index == 1) // Verde
                {
                    colors.push_back(1.0f); // R
                    colors.push_back(1.0f); // G
                    colors.push_back(0.0f); // B
                }
                else if (color_index == 2) // Azul
                {
                    colors.push_back(0.0f); // R
                    colors.push_back(1.0f); // G
                    colors.push_back(1.0f); // B
                }
            }
        }

        return colors;
    }

    std::vector<GLushort> Plane::generateIndices()
    {

    //    //// La malla tiene (segments + 1) x (segments + 1) vértices
    //    //int verticesPerRow = segments + 1;
    //    int actualVert = 1;

    //    for (int y = 0; y < segments; ++y) // Iterar por filas de la malla
    //    {
    //        for (int x = 0; x < segments; ++x) // Iterar por columnas de la malla
    //        {
    //            indices.push_back(actualVert);
    //            indices.push_back(actualVert - 1);
    //            indices.push_back(actualVert + segments);

    //            indices.push_back(actualVert);
    //            indices.push_back(actualVert + segments);
    //            indices.push_back(actualVert + segments + 1);

    //            actualVert++;
    //        }

    //        actualVert++;
    //    }

        std::vector<GLushort> indices;

        // Empezamos desde el vértice 0
        int actualVert = 0;

        for (int y = 0; y < segments; ++y) {
            for (int x = 0; x < segments; ++x) {
                // Cada cuadrado se convierte en dos triángulos:
                // 1. Primer triángulo
                indices.push_back(actualVert);
                indices.push_back(actualVert + 1);
                indices.push_back(actualVert + segments + 1);

                // 2. Segundo triángulo
                indices.push_back(actualVert + 1);
                indices.push_back(actualVert + segments + 2);
                indices.push_back(actualVert + segments + 1);

                actualVert++;
            }
            // Desplazamos al siguiente nivel de fila
            actualVert++;
        }

        return indices;
    }

    Plane::Plane()
    {
        auto coordinates = generateCoordinates();
        auto colors = generateColors();
        auto indices = generateIndices();

        std::cout << "Coordinates: ";
        for (const auto& coord : coordinates)
        {
            std::cout << coord << " ";
        }
        std::cout << std::endl;

        std::cout << "Colors: ";
        for (const auto& color : colors)
        {
            std::cout << color << " ";
        }
        std::cout << std::endl;

        std::cout << "Indices: ";
        for (const auto& index : indices)
        {
            std::cout << static_cast<int>(index) << " "; // Convertir a int para legibilidad si es GLubyte
        }
        std::cout << std::endl;

        numIndices = indices.size() * sizeof(GLubyte);

        glGenBuffers(3, vbo_ids);
        glGenVertexArrays(1, &vao_id);

        glBindVertexArray(vao_id);

        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[0]);
        glBufferData(GL_ARRAY_BUFFER, coordinates.size() * sizeof(GLfloat), coordinates.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[1]);
        glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), colors.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ids[2]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLubyte), indices.data(), GL_STATIC_DRAW);

    }

    Plane::~Plane()
    {
        glDeleteVertexArrays(1, &vao_id);
        glDeleteBuffers(3, vbo_ids);
    }

    void Plane::render()
    {
        glBindVertexArray(vao_id);
        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
        glBindVertexArray(0);
    }
}