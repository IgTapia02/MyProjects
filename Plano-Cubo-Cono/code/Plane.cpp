/**
    @author - Ignacio Tapia Marfil
*/

#include "Plane.hpp"

namespace OpenGLTapia
{

    std::vector<GLfloat> Plane::GenerateCoordinates()
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

    std::vector<GLfloat> Plane::GenerateColors()
    {
        std::vector<GLfloat> colors;

        for (int i = 0; i <= segments; ++i)
        {
            for (int j = 0; j <= segments; ++j)
            {
                int color_index = (i * (segments + 1) + j) % 3;
                if (color_index == 0)
                {
                    colors.push_back(1.0f);
                    colors.push_back(0.0f);
                    colors.push_back(1.0f);
                }
                else if (color_index == 1)
                {
                    colors.push_back(1.0f);
                    colors.push_back(1.0f);
                    colors.push_back(0.0f);
                }
                else if (color_index == 2)
                {
                    colors.push_back(0.0f);
                    colors.push_back(1.0f);
                    colors.push_back(1.0f);
                }
            }
        }

        return colors;
    }

    std::vector<GLushort> Plane::GenerateIndices()
    {
        std::vector<GLushort> indices;

        int actualVert = 0;

        for (int y = 0; y < segments; ++y) {
            for (int x = 0; x < segments; ++x) {

                indices.push_back(actualVert);
                indices.push_back(actualVert + 1);
                indices.push_back(actualVert + segments + 1);

                indices.push_back(actualVert + 1);
                indices.push_back(actualVert + segments + 2);
                indices.push_back(actualVert + segments + 1);

                actualVert++;
            }

            actualVert++;
        }

        return indices;
    }

    Plane::Plane()
    {
        auto coordinates = GenerateCoordinates();
        auto colors = GenerateColors();
        auto indices = GenerateIndices();

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

    void Plane::Render()
    {
        glBindVertexArray(vao_id);
        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
        glBindVertexArray(0);
    }
}