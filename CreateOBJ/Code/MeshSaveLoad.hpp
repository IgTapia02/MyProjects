/**
    @author - Ignacio Tapia Marfil
*/

#ifndef MESHSAVELOAD_HEADER
#define MESHSAVELOAD_HEADER

    #include <string>
    #include <vector>
    #include <glm/glm.hpp>

    #include "Mesh.hpp"

    namespace OpenGlTapia
    {
        class MeshSaveLoad 
        {

        public:

            static void SaveAsObj(const std::string& filePath,
                const std::vector<Mesh>& meshes,
                const std::vector<glm::mat4>& transforms);

        };
    }

#endif
