#include "game.h"

Game::Game(int width, int height, const string& title, const string& diffuse, bool fullscreen) : m_window(width, height, title, fullscreen),
                                                                                              m_diffuseTexture(diffuse),
                                                                                              m_diffuseShader("./res/diffuseShader", &player.camera, &m_lightSource, &m_diffuseMaterial),
                                                                                              m_fbs("./res/fbs"),
                                                                                              player(vec3(0, 5, -10), glm::radians(70.0f), float(width) / float(height), 0.01f, 1000.0f)
{
    m_diffuseMaterial = Material(vec3(1.0, 1.0, 1.0), vec3(1.0, 1.0, 1.0), vec3(1.0, 1.0, 1.0), 1.0f);
    m_sun = DirectionalLight(vec3(0.1, -0.5, -0.5), vec3(1.0f, 1.0f, 1.0f) * 0.33f, vec3(0.9f, 0.8f, 0.3f), vec3(1.0, 1.0, 1.0));
    m_moon = DirectionalLight(vec3(0.1, -0.5, -0.5), vec3(0.7f, 0.8f, 1.0f) * 0.1f, vec3(0.3f, 0.4f, 1.0f) * 0.1f, vec3(1.0, 1.0, 1.0));
    m_dayColor = vec3(0.2, 0.3, 1.0);
    m_nightColor = vec3(0.0, 0.0, 0.0);
    m_timeOfDay = 0.5f;
    updateLightSource();
}

// Game update function
void Game::update()
{
    advanceTimeOfDay();
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        switch(e.type)
        {
        case SDL_QUIT:
            m_window.close();
            break;
        case SDL_KEYDOWN:
            player.keyDown(e.key.keysym.scancode);
            break;
        case SDL_KEYUP:
            player.keyUp(e.key.keysym.scancode);
            break;
        case SDL_MOUSEMOTION:
            player.handleMouseInput(e.motion.xrel, e.motion.yrel);
            break;
        case SDL_MOUSEBUTTONDOWN:
            break;
        default:
            break;
        }
    }
    player.update();
}

// Do nothing until a key is pressed
void Game::waitForAnyKey()
{
    bool done = false;
    while(!done)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
            case SDL_QUIT:
            case SDL_KEYDOWN:
            case SDL_MOUSEBUTTONDOWN:
                done = true;
                break;
            case SDL_KEYUP:
            case SDL_MOUSEMOTION:
            default:
                break;
            }
        }
    }
}

// Add a renderer object to the diffuse or unlit renderers
void Game::createRenderer(MeshRenderer* mr, ShaderType type)
{
    switch(type)
    {
    case Diffuse:
        m_diffuseRenderers.push_back(mr);
        break;
    case Unlit:
        m_unlitRenderers.push_back(mr);
        break;
    default:
        break;
    }
}

// Update the current time in the day/night cycle
void Game::advanceTimeOfDay()
{
    m_timeOfDay += delta_time * days_per_second;
    if(m_timeOfDay > day_length)
    {
        m_timeOfDay -= 1.0f;
        //m_day++;
    }
    updateLightSource();
}

// Adjust light sources to time of day
void Game::updateLightSource()
{
    float lightVal = brightnessCurve(m_timeOfDay);
    m_clearColor = m_dayColor * lightVal;

    m_lightSource.diffuse = common::lerpv(m_moon.diffuse, m_sun.diffuse, lightVal);
    m_lightSource.ambient = common::lerpv(m_moon.ambient, m_sun.ambient, lightVal);
    m_lightSource.specular = common::lerpv(m_moon.specular, m_sun.specular, lightVal);
}

// Day / night cycle function
float Game::brightnessCurve(float x)
{
    if(x <= 0.2535)
    {
        // (4x - 0.2)^10
        return std::pow((4 * x) - 0.2, 10.0f);
    }
    else if(x < 0.7467)
    {
        // -(4x - 2)^10 + 1
        return -(std::pow((4 * x) - 2, 10.0f)) + 1;
    }
    else if(x <= 1.0f)
    {
        // (4x - 3.8)^10
        return std::pow((4 * x) - 3.8, 10.0f);
    }
    cout << "reached invalid value for x" << endl;
    return 0.0f;
}

// Render everything in the diffuse renderer list
void Game::draw()
{
    m_diffuseTexture.bind(0);
    m_window.clear(m_clearColor.x, m_clearColor.y, m_clearColor.z, 1.0f);
    glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, 1.0f);
    glBindFramebuffer(GL_FRAMEBUFFER, m_window.getFrameBuffer());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    m_diffuseShader.bind();
    cout << "Making " << m_diffuseRenderers.size() << " draw calls " << endl;
    for(unsigned i = 0; i < m_diffuseRenderers.size(); i++)
    {
        m_diffuseShader.update(m_diffuseRenderers[i]->getTransform());
        m_diffuseRenderers[i]->draw();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    m_fbs.bind();
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, m_window.getFrameBufferTexture());
    m_fbs.update();

    m_window.update();
}
