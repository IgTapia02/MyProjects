#ifndef MESHSAVELOAD_HEADER
#define MESHSAVELOAD_HEADER


    #include <string>
    #include <vector>
    #include <glm/glm.hpp>

    #include "Mesh.hpp"

    class MeshSaveLoad 
    {

    public:

        static void saveAsObj(const std::string& filePath,
            const std::vector<Mesh>& meshes,
            const std::vector<glm::mat4>& transforms);

    };


#endif
