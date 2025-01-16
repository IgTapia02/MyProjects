/**
    @author - Ignacio Tapia Marfil
*/

    #ifndef SCENE_HEADER
    #define SCENE_HEADER

    #include <SDL.h>
    #include <glad/glad.h>
    #include <glm/glm.hpp>
    #include <string>
    #include <vector>

    #include "Camera.hpp"
    #include "Mesh.hpp"
    #include "Ground.hpp"

    namespace OpenGlTapia
    {
        using glm::vec3;
        /** Clase para generar la escena principal
      */
        class Scene
        {
        private:

            enum
            {
                COORDINATES_VBO,
                COLORS_VBO,
                INDICES_EBO,
                VBO_COUNT
            };

            static const std::string   vertex_shader_code;
            static const std::string fragment_shader_code;

            GLuint  vbo_ids[VBO_COUNT];
            GLuint  vao_id;

            GLsizei number_of_indices;

            GLint   model_view_matrix_id;
            GLint   projection_matrix_id;

            const std::string& filePath; ///< Path del objeto que queremos instanciar.

            Mesh mesh;
            Ground ground; ///< Plano que vamos a usar como suelo.

            Camera camera;

        public:

            Scene(int width, int height, const std::string& _filePath);
            ~Scene();

            /// Bucle principal del programa.
            void   Update();

            /// Función para instanciar todas las Mesh necesarias y colocarlas en escena.
            void   Render();

            /// Función para reajustar las dimensiones y posiciones de la escena segun las dimensiones de la ventana.
            void   Resize(int width, int height);

        private:

            GLuint CompileShaders();
            void   ShowCompilationError(GLuint  shader_id);
            void   ShowLinkageError(GLuint program_id);

            /// Función para manejar los Inputs de teclado.
            void ProcessInput(const Uint8* keyboardState, float deltaTime);

            /// Función para manejar los Inputs de ratón.
            void ProcessMouseMotion(int xrel, int yrel);
        };

    }

#endif
