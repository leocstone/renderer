#ifndef FREELOOKCAMERA_H
#define FREELOOKCAMERA_H
#include "camera.h"
#include <SDL2/SDL.h>
#include "engine_constants.h"

/*

FreeLookCamera

Implements free look controls for an instance of the Camera class

*/
class FreeLookCamera
{
public:
    FreeLookCamera();
    FreeLookCamera(const vec3& pos, float fov, float aspect, float zNear, float zFar);
    ~FreeLookCamera() {}

    void update();
    void move(const vec3& delta);
    void keyDown(SDL_Scancode c);
    void keyUp(SDL_Scancode c);
    void handleMouseInput(Sint32 xrel, Sint32 yrel);

    Camera camera;

private:

    bool m_keyDown[SDL_NUM_SCANCODES];
    float m_sensitivity;
    float m_moveSpeed;
    float m_sprintSpeed;
    vec3 m_acceleration;
    inline void init();
};

#endif // FREELOOKCAMERA_H
