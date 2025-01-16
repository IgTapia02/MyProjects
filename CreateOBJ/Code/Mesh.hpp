/**
    @author - Ignacio Tapia Marfil
*/

#ifndef MESH_HEADER
#define MESH_HEADER

    #include <glad/glad.h>
    #include <glm/glm.hpp>
    #include <string>
    #include <vector>
    namespace OpenGlTapia
    {

        class Mesh
        {
        private:
            GLuint vaoID;
            GLuint vboIDs[3]; 
            GLuint textureID;
            size_t numberOfIndices;

            std::vector<glm::vec3> vertices;
            std::vector<glm::vec3> colors;
            std::vector<GLshort> indices;
            std::vector<glm:: vec2 > textCoords;

        public:
            Mesh(const std::string& filePath);
            ~Mesh();

            void Render(GLuint modelViewMatrixID, const glm::mat4& modelMatrix);

            // Métodos get
            const std::vector<glm::vec3>& GetVertices() const { return vertices;}
            const std::vector<glm::vec3>& GetColors()   const { return colors;}
            const std::vector<GLshort>&   GetIndices()  const { return indices;}

        private:
            void LoadFromFile(const std::string& filePath);
            glm::vec3 SetColor();
        };
    }

#endif