/**
    @author - Ignacio Tapia Marfil
*/

#include "Mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/gtc/type_ptr.hpp>     

namespace OpenGlTapia
{

    Mesh::Mesh(const std::string& filePath)
        : vaoID(0), numberOfIndices(0)
    {
        glGenBuffers(3, vboIDs);
        glGenVertexArrays(1, &vaoID);
        glGenVertexArrays(1, &vaoID);
        LoadFromFile(filePath);
    }

    Mesh::~Mesh()
    {
        glDeleteVertexArrays(1, &vaoID);
        glDeleteBuffers(3, vboIDs);
    }

    void Mesh::LoadFromFile(const std::string& filePath)
    {
        Assimp::Importer importer;

        auto scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

        auto mesh = scene->mMeshes[0];
        size_t numVertices = mesh->mNumVertices;

        glBindVertexArray(vaoID);

        vertices.resize(numVertices);
        for (size_t i = 0; i < numVertices; ++i) {
            vertices[i] = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        }
        glBindBuffer(GL_ARRAY_BUFFER, vboIDs[0]);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        colors.resize(numVertices);
        for (size_t i = 0; i < numVertices; ++i) {
            colors[i] = SetColor();
        }
        glBindBuffer(GL_ARRAY_BUFFER, vboIDs[1]);
        glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

        numberOfIndices = mesh->mNumFaces * 3;
        indices.resize(numberOfIndices);
        auto indexPtr = indices.begin();

        for (unsigned i = 0; i < mesh->mNumFaces; ++i) 
        {
            auto& face = mesh->mFaces[i];
            assert(face.mNumIndices == 3);

            *indexPtr++ = face.mIndices[0];
            *indexPtr++ = face.mIndices[1];
            *indexPtr++ = face.mIndices[2];
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIDs[2]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLshort), indices.data(), GL_STATIC_DRAW);
    }

    void Mesh::Render(GLuint modelViewMatrixID, const glm::mat4& modelMatrix)
    {
        glUniformMatrix4fv(modelViewMatrixID, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glBindVertexArray(vaoID);
        glDrawElements(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_SHORT, 0);
    }

    glm::vec3 Mesh::SetColor()
    {
        return glm::vec3(1.f,1.f,1.f);
    }
}