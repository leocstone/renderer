#ifndef GAME_H
#define GAME_H
#include "window.h"
#include "meshrenderer.h"
#include "diffuseshader.h"
#include "framebuffershader.h"
#include "freelookcamera.h"
#include "common.h"
#include <vector>

using std::vector;

enum ShaderType
{
    Diffuse,
    Unlit
};

/*

Game

Runs the main game loop, gets input, and manages all resources needed for the renderer

*/
class Game
{
public:
    Game(int width, int height, const string& title, const string& diffuse, bool fullscreen);
    ~Game() {}

    void update();
    void updateLightSource();
    void advanceTimeOfDay();
    void draw();
    void waitForAnyKey();
    void swapWindow() { m_window.update(); }

    void createRenderer(MeshRenderer* mr, ShaderType type);
    bool isClosed() { return m_window.isClosed(); }

    FreeLookCamera player;

private:
    Window m_window;
    float brightnessCurve(float x);

    vector<MeshRenderer*> m_diffuseRenderers;
    vector<MeshRenderer*> m_unlitRenderers;
    Texture m_diffuseTexture;
    DiffuseShader m_diffuseShader;
    Material m_diffuseMaterial;
    DirectionalLight m_lightSource;
    DirectionalLight m_moon;
    DirectionalLight m_sun;
    vec3 m_dayColor;
    vec3 m_nightColor;
    FramebufferShader m_fbs;
    vec3 m_clearColor;
    float m_timeOfDay;
};

#endif // GAME_H
