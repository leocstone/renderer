#include "window.h"

Window::Window(int width, int height, const string& title, bool fullscreen)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    Uint32 flags = SDL_WINDOW_OPENGL;

    if(fullscreen)
    {
        flags |= SDL_WINDOW_FULLSCREEN;
    }

    // Lock cursor
    SDL_SetRelativeMouseMode(SDL_TRUE);

    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);

    m_glContext = SDL_GL_CreateContext(m_window);

    GLenum status = glewInit();

    if(status != GLEW_OK)
    {
        cout << "Error: Glew initialization failed" << endl;
        cout << status << endl;
    }

    glGenFramebuffers(1, &m_frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
    glGenTextures(1, &m_frameBufferTexture);
    glBindTexture(GL_TEXTURE_2D, m_frameBufferTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_frameBufferTexture, 0);

    glGenRenderbuffers(1, &m_renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBuffer);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        cout << "Error: Could not create framebuffer" << endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    m_closed = false;

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glEnable(GL_FRAMEBUFFER_SRGB);
    glEnable(GL_MULTISAMPLE);
    glFrontFace(GL_CCW);
    glClearDepth(GL_TRUE);
    glCullFace(GL_BACK);
}

Window::~Window()
{
    glDeleteFramebuffers(1, &m_frameBuffer);
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Window::clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update()
{
    SDL_GL_SwapWindow(m_window);
}
