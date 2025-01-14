

#include "Cone.hpp"
#include <cmath> // Para usar sin() y cos()

namespace SDLTapia
{

    std::vector<GLfloat> Cone::generateCoordinates()
    {
        std::vector<GLfloat> coordinates;

        // Centro Inferior
        coordinates.push_back(0.0f); // Centro x
        coordinates.push_back(0.0f); // Centro y
        coordinates.push_back(0.0f); // Centro z

        // Vértices de la base (el primer vértice está en (RADIUS, 0.0f, 0.0f))
        coordinates.push_back(radius); // x
        coordinates.push_back(0.0f);   // y
        coordinates.push_back(0.0f);   // z

        // Vértices restantes de la base aplicando el ángulo
        for (int i = 1; i < segments; ++i)
        {
            float angle = 2.0f * 3.14159265358979323846 * i / segments;
            coordinates.push_back(radius * cos(angle)); // x
            coordinates.push_back(0.0f);                // y
            coordinates.push_back(radius * sin(angle)); // z
        } 

        // Vértice superior del cono
        coordinates.push_back(0.0f);   // x
        coordinates.push_back(height); // y
        coordinates.push_back(0.0f);   // z

        return coordinates;
    }

    std::vector<GLfloat> Cone::generateColors()
    {
        std::vector<GLfloat> colors;

        // Color del vértice superior
        colors.push_back(1.0f); // R
        colors.push_back(0.0f); // G
        colors.push_back(0.0f); // B

        // Colores para la base
        for (int i = 0; i < segments; ++i)
        {
            colors.push_back(0.0f); // R
            colors.push_back(0.0f); // G
            colors.push_back(1.0f); // B
        }

        colors.push_back(0.0f);      // R
        colors.push_back(0.0f);      // G
        colors.push_back(1.0f);      // B

        colors.push_back(0.0f);      // R
        colors.push_back(1.0f);      // G
        colors.push_back(0.0f);      // B

        return colors;
    }

    std::vector<GLubyte> Cone::generateIndices()
    {
        std::vector<GLubyte> indices;

        // Índices para las caras laterales
        for (int i = 1; i <= segments; ++i)
        {
            indices.push_back(i); // Vértice actual
            indices.push_back(segments + 1); // Vértice superior

            if (i != segments)
                indices.push_back(i + 1); // Siguiente vértice
            else
                indices.push_back(1);
        }

        // Índices para la base
        for (int i = 1; i <= segments; ++i)
        {
            if (i != segments)
                indices.push_back(i + 1); // Siguiente vértice
            else
                indices.push_back(1);

            indices.push_back(0);        // Centro de la base
            indices.push_back(i);                      // Vértice actual

            
        }

        return indices;
    }

    Cone::Cone()
    {
        // Generar datos del cono
        auto coordinates = generateCoordinates();
        auto colors = generateColors();
        auto indices = generateIndices();

        numIndices = indices.size();
        
        // Crear VAO y VBOs
        glGenBuffers(3, vbo_ids);
        glGenVertexArrays(1, &vao_id);
        
        glBindVertexArray(vao_id);

        // VBO de coordenadas
        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[0]);
        glBufferData(GL_ARRAY_BUFFER, coordinates.size() * sizeof(GLfloat), coordinates.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // VBO de colores
        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[1]);
        glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), colors.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // VBO de índices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ids[2]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLubyte), indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    Cone::~Cone()
    {
        glDeleteVertexArrays(1, &vao_id);
        glDeleteBuffers(3, vbo_ids);
    }

    void Cone::render()
    {
        glBindVertexArray(vao_id);
        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_BYTE, 0);
        glBindVertexArray(0);
    }

}