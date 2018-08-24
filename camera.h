#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include "transform.h"
#include "extra_operators.h"

constexpr float min_rotation = -1.3f;
constexpr float max_rotation = 1.0f;

/*

Camera

Used to calculate projection matrix for rendering objects

*/
class Camera
{
public:
    Camera(const vec3& pos, float fov, float aspect, float zNear, float zFar) : m_horizontalAngle(0), m_verticalAngle(0)
    {
        m_fov = fov;
        m_aspect = aspect;
        m_near = zNear;
        m_far = zFar;
        position = pos;
        velocity = vec3(0, 0, 0);
        acceleration = vec3(0, 0, 0);

        m_perspective = glm::perspective(fov, aspect, zNear, zFar);
        m_up = vec3(0, 1, 0);
        m_forward = vec3(0, 0, 1);
        m_right = calcRight();
    }

    // Returns the view projection matrix of the camera
    glm::mat4 getViewProjection() const
    {
        return m_perspective * glm::lookAt(position, position + m_forward, m_up);
    }

    vec3 calcUp() const
    {
        return glm::cross(m_right, m_forward);
    }

    vec3 getUp() const
    {
        return m_up;
    }

    vec3 calcForward() const
    {
        return vec3(
                          glm::cos(m_verticalAngle) * glm::sin(m_horizontalAngle),
                          glm::sin(m_verticalAngle),
                          glm::cos(m_verticalAngle) * glm::cos(m_horizontalAngle)
                        );
    }

    vec3 getForward() const
    {
        return m_forward;
    }

    vec3 calcRight() const
    {
        return vec3(glm::sin(m_horizontalAngle - half_pi), 0, glm::cos(m_horizontalAngle - half_pi));
    }

    vec3 getRight() const
    {
        return m_right;
    }

    // Rotation along Y and Z axes
    void rotate(float horizontalAngle, float verticalAngle)
    {
        m_horizontalAngle += horizontalAngle;
        m_verticalAngle += verticalAngle;

        m_forward = calcForward();

        m_right = calcRight();

        m_up = calcUp();

        // Recalculate perspective matrix
        m_perspective = glm::perspective(m_fov, m_aspect, m_near, m_far);

        if(m_verticalAngle > max_rotation)
        {
            m_verticalAngle = max_rotation;
        }
        if(m_verticalAngle < min_rotation)
        {
            m_verticalAngle = min_rotation;
        }
    }

    void move(const vec3& delta)
    {
        position += delta;
    }

    float getHorizontalAngle() { return m_horizontalAngle; }
    float getVerticalAngle() { return m_verticalAngle; }

    vec3 position;
    vec3 velocity;
    vec3 acceleration;

private:
    glm::mat4 m_perspective;

    vec3 m_up;
    vec3 m_forward;
    vec3 m_right;

    float m_horizontalAngle;
    float m_verticalAngle;

    float m_fov;

    // aspect ratio - WIDTH / HEIGHT
    float m_aspect;

    // near and far planes
    float m_near;
    float m_far;

    inline float degreesToRadians(float deg) { return deg * pi / 180.0; }
};

#endif // CAMERA_H
