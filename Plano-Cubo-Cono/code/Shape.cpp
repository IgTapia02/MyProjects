

#include "Shape.hpp"

namespace SDLTapia
{

    void Shape::genCoordinates(Point3D startPoint, GLfloat width)
    {
        coordinates =
        {
            startPoint.getX()         ,startPoint.getY()         ,startPoint.getZ(),

            startPoint.getX() + width ,startPoint.getY()         ,startPoint.getZ(),

            startPoint.getX() + width ,startPoint.getY() + width ,startPoint.getZ(),

            startPoint.getX()         ,startPoint.getY() + width ,startPoint.getZ(),
        };
        indices =
        {
            0,1,2,
            0,2,3

        };
    }

    Shape::Shape(Point3D startPoint, GLfloat width, GLfloat heigth)
    {
        genCoordinates(startPoint, width);

        colors =
        {
            0,0,0,
            0,0,0,
            0,0,0,
            0,0,0,
        };

        // Se generan índices para los VBOs del cubo:

        glGenBuffers(VBO_COUNT, vbo_ids);
        glGenVertexArrays(1, &vao_id);

        // Se activa el VAO del cubo para configurarlo:

        glBindVertexArray(vao_id);

        // Se suben a un VBO los datos de coordenadas y se vinculan al VAO:

        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[COORDINATES_VBO]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(coordinates), coordinates.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // Se suben a un VBO los datos de color y se vinculan al VAO:

        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[COLORS_VBO]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // Se suben a un EBO los datos de índices:

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ids[INDICES_EBO]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    Shape::Shape()
    {
        Point3D point;

        genCoordinates(point, 1);

        colors =
        {
            0,0,0,
            0,0,0,
            0,0,0,
            0,0,0,
        };

        // Se generan índices para los VBOs del cubo:

        glGenBuffers(VBO_COUNT, vbo_ids);
        glGenVertexArrays(1, &vao_id);

        // Se activa el VAO del cubo para configurarlo:

        glBindVertexArray(vao_id);

        // Se suben a un VBO los datos de coordenadas y se vinculan al VAO:

        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[COORDINATES_VBO]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(coordinates), coordinates.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // Se suben a un VBO los datos de color y se vinculan al VAO:

        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[COLORS_VBO]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // Se suben a un EBO los datos de índices:

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ids[INDICES_EBO]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    Shape::~Shape()
    {
        // Se liberan los VBOs y el VAO usados:

        glDeleteVertexArrays(1, &vao_id);
        glDeleteBuffers(VBO_COUNT, vbo_ids);
    }

    void Shape::render()
    {
        // Se selecciona el VAO que contiene los datos del objeto y se dibujan sus elementos:

        glBindVertexArray(vao_id);
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_BYTE, 0);
        glBindVertexArray(0);
    }
}