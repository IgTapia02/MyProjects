/**
    @author - Ignacio Tapia Marfil
*/

#include "Cube.hpp"
#include <iostream>


namespace OpenGLTapia
{

    const GLfloat Cube::coordinates[] =
    {
       -1,-1,+1,
       +1,-1,+1,
       +1,+1,+1,
       -1,+1,+1,
       -1,-1,-1,
       +1,-1,-1,
       +1,+1,-1,
       -1,+1,-1,
    };

    const GLfloat Cube::colors[] =
    {
        0, 0, 1,
        1, 0, 1,
        1, 1, 1,
        0, 1, 1,
        0, 0, 0,
        1, 0, 0,
        1, 1, 0,
        0, 1, 0,
    };

    const GLubyte Cube::indices[] =
    {
        0, 1, 2,
        0, 2, 3,
        4, 0, 3,
        4, 3, 7,
        7, 5, 4,
        7, 6, 5,
        1, 5, 6,
        1, 6, 2,
        3, 2, 6,
        3, 6, 7,
        5, 0, 4,
        5, 1, 0,
    };

    Cube::Cube()
    {

        glGenBuffers(3, vbo_ids);
        glGenVertexArrays(1, &vao_id);

        glBindVertexArray(vao_id);

        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(coordinates), coordinates, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ids[2]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    }

    Cube::~Cube()
    {
        glDeleteVertexArrays(1, &vao_id);
        glDeleteBuffers     (3, vbo_ids);
    }
    
    void Cube::Render()
    {
        glBindVertexArray   (vao_id);
        glDrawElements      (GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_BYTE, 0);
        glBindVertexArray   (0);
    }
}