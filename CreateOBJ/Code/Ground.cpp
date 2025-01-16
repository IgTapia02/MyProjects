/**
    @author - Ignacio Tapia Marfil
*/

#include "Ground.hpp"
#include <iostream>
#include "../../../libs/stb/include/stb_image.h"

namespace OpenGlTapia
{

    GLuint Ground::loadHeightMap(const std::string& path, int& width, int& height)
    {
        int channels;
        unsigned char* image = stbi_load(path.c_str(), &width, &height, &channels, 1);

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

        stbi_image_free(image);
        return textureID;
    }

    std::vector<GLfloat> Ground::GenerateCoordinates()
    {
        std::vector<GLfloat> coordinates;

        float x = 0.f;
        float y = 0.f;

        int heightMapWidth, heightMapHeight;

        unsigned char* heightMapData = stbi_load("../../../assets/HeightMap2.png", &heightMapWidth, &heightMapHeight, nullptr, 1);

        if (!heightMapData) {
            std::cerr << "Error al cargar el height map" << std::endl;
            return coordinates;
        }

        float segmentWidth = length_X / segments;
        float segmentHeight = length_Y / segments;

        for (int i = 0; i <= segments; ++i)
        {
            for (int j = 0; j <= segments; ++j)
            {
                coordinates.push_back(x);

                float normalizedX = static_cast<float>(j) / segments;
                float normalizedY = static_cast<float>(i) / segments;

                int texX = static_cast<int>(normalizedX * (heightMapWidth - 1));
                int texY = static_cast<int>(normalizedY * (heightMapHeight - 1));

                unsigned char pixelValue = heightMapData[texY * heightMapWidth + texX];

                GLfloat heightValue = static_cast<GLfloat>(pixelValue) / 255.0f * 500.0f;

                coordinates.push_back(heightValue);

                coordinates.push_back(y);

                x += segmentWidth;
            }

            x = 0.f;
            y += segmentHeight;
        }

        stbi_image_free(heightMapData);

        return coordinates;
    }

    std::vector<GLfloat> Ground::GenerateColors()
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

    std::vector<GLushort> Ground::GenerateIndices()
    {
        std::vector<GLushort> indices;

        int actualVert = 0;

        for (int y = 0; y < segments * 2; ++y) 
        {
            for (int x = 0; x < segments; ++x) 
            {

                indices.push_back(actualVert + 1);
                indices.push_back(actualVert);
                indices.push_back(actualVert + segments + 1);

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
        auto coordinates = GenerateCoordinates();
        auto colors      = GenerateColors();
        auto indices     = GenerateIndices();

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

    void Ground::Render()
    {
        glBindVertexArray(vao_id);
        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
        glBindVertexArray(0);
    }

}
