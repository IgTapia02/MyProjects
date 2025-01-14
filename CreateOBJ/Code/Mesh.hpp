#ifndef MESH_HEADER
#define MESH_HEADER

    #include <glad/glad.h>
    #include <glm/glm.hpp>
    #include <string>
    #include <vector>

    class Mesh
    {
    private:
        GLuint vaoID;
        GLuint vboIDs[3]; 
        GLuint textureID;
        size_t numberOfIndices;

        // Nuevos miembros para almacenar los datos de la malla
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> colors;
        std::vector<GLshort> indices;
        std::vector<glm:: vec2 > textCoords;


    public:

        Mesh(const std::string& filePath);
        ~Mesh();

        void render(GLuint modelViewMatrixID, const glm::mat4& modelMatrix);

        // Métodos get
        const std::vector<glm::vec3>& getVertices() const { return vertices; }
        const std::vector<glm::vec3>& getColors() const { return colors; }
        const std::vector<GLshort>& getIndices() const { return indices; }

    private:
        void loadFromFile(const std::string& filePath);
        glm::vec3 randomColor();
    };

#endif