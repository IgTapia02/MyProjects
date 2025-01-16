/**
    @author - Ignacio Tapia Marfil
*/

#ifndef CAMERA_H
#define CAMERA_H

    #include <glm/glm.hpp>
    #include <glm/gtc/matrix_transform.hpp>
    #include <glm/gtc/type_ptr.hpp>

    #include <iostream>
        namespace OpenGLTapia
        {

            enum CameraMovement {
                FORWARD,
                BACKWARD,
                LEFT,
                RIGHT
            };

            class Camera {
            public:

                glm::vec3 Position;
                glm::vec3 Front;
                glm::vec3 Up;
                glm::vec3 Right;
                glm::vec3 WorldUp;

                float Yaw;
                float Pitch;

                float MovementSpeed;
                float MouseSensitivity;
                float Zoom;

                Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
                    : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
                    MovementSpeed(2.5f), MouseSensitivity(0.1f), Zoom(45.0f) 
                {
                    Position = position;
                    WorldUp = up;
                    Yaw = yaw;
                    Pitch = pitch;
                    UpdateCameraVectors();
                }

                glm::mat4 GetViewMatrix() {
                    return glm::lookAt(Position, Position + Front, Up);
                }

                void ProcessKeyboard(CameraMovement direction, float deltaTime) {

                    float velocity = MovementSpeed * deltaTime;
                    if (direction == FORWARD)
                        Position += Front * velocity;
                    if (direction == BACKWARD)
                        Position -= Front * velocity;
                    if (direction == LEFT)
                        Position -= Right * velocity;
                    if (direction == RIGHT)
                        Position += Right * velocity;
                }

                void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true) {
                    xoffset *= MouseSensitivity;
                    yoffset *= MouseSensitivity;

                    Yaw += xoffset;
                    Pitch -= yoffset;

                    if (constrainPitch) {
                        if (Pitch > 89.0f)
                            Pitch = 89.0f;
                        if (Pitch < -89.0f)
                            Pitch = -89.0f;
                    }

                    UpdateCameraVectors();
                }

                void ProcessMouseScroll(float yoffset) {
                    Zoom -= yoffset;
                    if (Zoom < 1.0f)
                        Zoom = 1.0f;
                    if (Zoom > 45.0f)
                        Zoom = 45.0f;
                }

            private:

                void UpdateCameraVectors() {
                    glm::vec3 front;
                    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
                    front.y = sin(glm::radians(Pitch));
                    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
                    Front = glm::normalize(front);

                    Right = glm::normalize(glm::cross(Front, WorldUp));
                    Up = glm::normalize(glm::cross(Right, Front));
                }

            public:
                const glm::mat4& get_projection_matrix() const
                {
                    return projection_matrix;
                }

                glm::mat4 get_transform_matrix_inverse() const
                {
                    return glm::lookAt
                    (
                        glm::vec3(Position[0], Position[1], Position[2]),
                        glm::vec3(target[0], target[1], target[2]),
                        glm::vec3(0.0f, 1.0f, 0.0f)
                    );
                }
            };
        }

#endif