#include "freelookcamera.h"

FreeLookCamera::FreeLookCamera() : camera(vec3(0, 0, 0), glm::radians(70.0f), 16.0f / 9.0f, 1.0f, 400.0f)
{
    init();
}


FreeLookCamera::FreeLookCamera(const vec3& pos, float fov, float aspect, float zNear, float zFar) : camera(pos, fov, aspect, zNear, zFar)
{
    init();
}

void FreeLookCamera::update()
{
    float moveSpeed = m_moveSpeed;
    if(m_keyDown[SDL_SCANCODE_LSHIFT])
    {
        m_moveSpeed = m_sprintSpeed;
    }
    if(m_keyDown[SDL_SCANCODE_W])
    {
        m_acceleration += camera.getForward() * moveSpeed;
    }
    if(m_keyDown[SDL_SCANCODE_S])
    {
        m_acceleration += camera.getForward() * -moveSpeed;
    }
    if(m_keyDown[SDL_SCANCODE_D])
    {
        m_acceleration += camera.getRight() * moveSpeed;
    }
    if(m_keyDown[SDL_SCANCODE_A])
    {
        m_acceleration += camera.getRight() * -moveSpeed;
    }
    camera.velocity *= default_friction;
    camera.velocity += m_acceleration;
    camera.position = camera.velocity * delta_time;
}

void FreeLookCamera::move(const vec3& delta)
{
    camera.move(delta);
}

void FreeLookCamera::keyDown(SDL_Scancode c)
{
    m_keyDown[c] = true;
}

void FreeLookCamera::keyUp(SDL_Scancode c)
{
    m_keyDown[c] = false;
}

void FreeLookCamera::handleMouseInput(Sint32 xrel, Sint32 yrel)
{
    float horizontalChange = 0;
    float verticalChange = 0;
    horizontalChange = m_sensitivity * delta_time * float(-xrel);
    verticalChange = m_sensitivity * delta_time * float(-yrel);
    camera.rotate(horizontalChange, verticalChange);
}

void FreeLookCamera::init()
{
    m_sensitivity = default_sensitivity;
    m_moveSpeed = player_speed;
    m_sprintSpeed = player_sprint_speed;
    memset(&m_keyDown[0], 0, SDL_NUM_SCANCODES);
    camera.acceleration = vec3(0, default_gravity, 0);
}
