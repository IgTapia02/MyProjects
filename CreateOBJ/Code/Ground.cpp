#include "Ground.hpp"
#include <iostream>
#include "../../../libs/stb/include/stb_image.h"

namespace udit
{

    // Función para cargar la imagen del height map
    GLuint Ground::loadHeightMap(const std::string& path, int& width, int& height)
    {
        int channels;
        unsigned char* image = stbi_load(path.c_str(), &width, &height, &channels, 1); // Cargar como imagen en escala de grises

        if (!image) {
            std::cerr << "Error al cargar el height map: " << path << std::endl;
            return 0;
        }

        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, image);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(image); // Liberar memoria después de cargar la imagen
        return textureID;
    }

    std::vector<GLfloat> Ground::generateCoordinates()
    {
        std::vector<GLfloat> coordinates;

        float x = 0.f;
        float y = 0.f;

        // Cargar el height map
        int heightMapWidth, heightMapHeight;

        unsigned char* heightMapData = stbi_load("../../../assets/HeightMap2.png", &heightMapWidth, &heightMapHeight, nullptr, 1); // Cargar como escala de grises

        if (!heightMapData) {
            std::cerr << "Error al cargar el height map" << std::endl;
            return coordinates;
        }

        // Calcular el tamaño de cada segmento
        float segmentWidth = length_X / segments;
        float segmentHeight = length_Y / segments;

        for (int i = 0; i <= segments; ++i)
        {
            for (int j = 0; j <= segments; ++j)
            {
                coordinates.push_back(x); // Posición X del vértice en el plano

                // Mapear las coordenadas del vértice (x, y) al rango del height map
                float normalizedX = static_cast<float>(j) / segments; // Normalizar j al rango [0, 1]
                float normalizedY = static_cast<float>(i) / segments; // Normalizar i al rango [0, 1]

                // Calcular las coordenadas del height map en píxeles
                int texX = static_cast<int>(normalizedX * (heightMapWidth - 1));
                int texY = static_cast<int>(normalizedY * (heightMapHeight - 1));

                // Obtener el valor de altura del height map
                unsigned char pixelValue = heightMapData[texY * heightMapWidth + texX]; // Acceder al píxel correspondiente

                GLfloat heightValue = static_cast<GLfloat>(pixelValue) / 255.0f * 500.0f; // Escalar el valor del height map a la altura deseada

                coordinates.push_back(heightValue); // Usar la altura como la coordenada Z


                coordinates.push_back(y); // Posición Y del vértice en el plano

                x += segmentWidth; // Incrementar la posición X del plano
            }

            x = 0.f; // Reiniciar X para la siguiente fila
            y += segmentHeight; // Incrementar la posición Y del plano
        }

        stbi_image_free(heightMapData); // Liberar la memoria del height map

        return coordinates;
    }

    std::vector<GLfloat> Ground::generateColors()
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

    std::vector<GLushort> Ground::generateIndices()
    {
        std::vector<GLushort> indices;

        // Empezamos desde el vértice 0
        int actualVert = 0;

        for (int y = 0; y < segments * 2; ++y) 
        {
            for (int x = 0; x < segments; ++x) 
            {

                // Cada cuadrado se convierte en dos triángulos:
                // 1. Primer triángulo
                indices.push_back(actualVert + 1);
                indices.push_back(actualVert);
                indices.push_back(actualVert + segments + 1);

                // 2. Segundo triángulo
                indices.push_back(actualVert + segments + 2);
                indices.push_back(actualVert + 1);
                indices.push_back(actualVert + segments + 1);

                actualVert++;
            }
            actualVert++;
        }

        return indices;
    }

    Ground::Ground()
    {
        auto coordinates = generateCoordinates();
        auto colors = generateColors();
        auto indices = generateIndices();

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

    Ground::~Ground()
    {
        glDeleteVertexArrays(1, &vao_id);
        glDeleteBuffers(3, vbo_ids);
    }

    void Ground::render()
    {
        glBindVertexArray(vao_id);
        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
        glBindVertexArray(0);
    }

}
