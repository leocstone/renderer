#ifndef WINDOW_H
#define WINDOW_H
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

/*

Window

Creates and manages an SDL2 window with an OpenGL context, and provides access to the framebuffer

*/
class Window
{
public:
    Window(int width, int height, const string& title, bool fullscreen);
    ~Window();

    void clear(float r, float g, float b, float a);
    void update();
    void close() { m_closed = true; }
    bool isClosed() { return m_closed; }
    GLuint getFrameBuffer() { return m_frameBuffer; }
    GLuint getFrameBufferTexture() { return m_frameBufferTexture; }

private:
    SDL_Window* m_window;
    SDL_GLContext m_glContext;

    bool m_closed;

    GLuint m_frameBuffer;
    GLuint m_frameBufferTexture;
    GLuint m_renderBuffer;
};

#endif // WINDOW_H
