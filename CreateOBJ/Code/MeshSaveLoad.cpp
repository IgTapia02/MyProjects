
#include "MeshSaveLoad.hpp"


#include <iostream>
#include <fstream>

void MeshSaveLoad::saveAsObj(const std::string& filePath,
    const std::vector<Mesh>& meshes,
    const std::vector<glm::mat4>& transforms)
{
    std::ofstream file(filePath);

    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo para guardar el OBJ.");
    }

    size_t vertexOffset = 0;

    for (size_t i = 0; i < meshes.size(); ++i) {
        const auto& mesh = meshes[i];
        const auto& transform = transforms[i];

        // Transformar y guardar vértices
        const auto& vertices = mesh.getVertices();
        for (const auto& vertex : vertices) {
            glm::vec4 transformedVertex = transform * glm::vec4(vertex, 1.0f);
            file << "v " << transformedVertex.x << " "
                << transformedVertex.y << " "
                << transformedVertex.z << "\n";
        }

        // Guardar colores como comentario
        const auto& colors = mesh.getColors();
        for (const auto& color : colors) {
            file << "# Color: " << color.r << " " << color.g << " " << color.b << "\n";
        }

        // Guardar índices ajustados por el offset
        const auto& indices = mesh.getIndices();
        for (size_t j = 0; j < indices.size(); j += 3) {
            file << "f " << (indices[j] + 1 + vertexOffset) << " "
                << (indices[j + 1] + 1 + vertexOffset) << " "
                << (indices[j + 2] + 1 + vertexOffset) << "\n";
        }

        vertexOffset += vertices.size(); // Actualizar el offset
    }

    file.close();
}
