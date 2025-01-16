/**
    @author - Ignacio Tapia Marfil
*/

#include "Cone.hpp"
#include <cmath>

namespace OpenGLTapia
{

    std::vector<GLfloat> Cone::GenerateCoordinates()
    {
        std::vector<GLfloat> coordinates;

        coordinates.push_back(0.0f);
        coordinates.push_back(0.0f);
        coordinates.push_back(0.0f);

        coordinates.push_back(radius);
        coordinates.push_back(0.0f);
        coordinates.push_back(0.0f);

        for (int i = 1; i < segments; ++i)
        {
            float angle = 2.0f * 3.14159265358979323846 * i / segments;
            coordinates.push_back(radius * cos(angle));
            coordinates.push_back(0.0f);              
            coordinates.push_back(radius * sin(angle));
        } 

        coordinates.push_back(0.0f);
        coordinates.push_back(height);
        coordinates.push_back(0.0f);

        return coordinates;
    }

    std::vector<GLfloat> Cone::GenerateColors()
    {
        std::vector<GLfloat> colors;

        colors.push_back(1.0f);
        colors.push_back(0.0f);
        colors.push_back(0.0f);

        // Colores para la base
        for (int i = 0; i < segments; ++i)
        {
            colors.push_back(0.0f);
            colors.push_back(0.0f);
            colors.push_back(1.0f);
        }

        colors.push_back(0.0f);
        colors.push_back(0.0f);
        colors.push_back(1.0f);

        colors.push_back(0.0f);
        colors.push_back(1.0f);
        colors.push_back(0.0f);

        return colors;
    }

    std::vector<GLubyte> Cone::GenerateIndices()
    {
        std::vector<GLubyte> indices;

        for (int i = 1; i <= segments; ++i)
        {
            indices.push_back(i);
            indices.push_back(segments + 1);

            if (i != segments)
                indices.push_back(i + 1);
            else
                indices.push_back(1);
        }

        // Índices para la base
        for (int i = 1; i <= segments; ++i)
        {
            if (i != segments)
                indices.push_back(i + 1);
            else
                indices.push_back(1);

            indices.push_back(0);
            indices.push_back(i);            
        }

        return indices;
    }

    Cone::Cone()
    {

        auto coordinates = GenerateCoordinates();
        auto colors = GenerateColors();
        auto indices = GenerateIndices();

        numIndices = indices.size();
        
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

        glBindVertexArray(0);
    }

    Cone::~Cone()
    {
        glDeleteVertexArrays(1, &vao_id);
        glDeleteBuffers(3, vbo_ids);
    }

    void Cone::Render()
    {
        glBindVertexArray(vao_id);
        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_BYTE, 0);
        glBindVertexArray(0);
    }

}