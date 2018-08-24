#ifndef FRAMEBUFFERSHADER_H
#define FRAMEBUFFERSHADER_H
#include "shader.h"

/*

FramebufferShader

Manages an OpenGL framebuffer and a shader to draw it

*/
class FramebufferShader : public Shader
{
public:

    FramebufferShader() {}
    FramebufferShader(const string& fileName);
    ~FramebufferShader();

    void update();

private:

    // Create a quad that covers the whole screen
    void initQuad();

    // Fragment shader, vertex shader
    static const unsigned NUM_SHADERS = 2;

    GLuint m_shaders[NUM_SHADERS];

    static const unsigned m_quadDrawCount = 6;

    enum
    {
        QUAD_POSITION,
        QUAD_TEXCOORD,

        NUM_QUAD_BUFFERS
    };

    GLuint m_quadVao;
    GLuint m_quadBuffers[NUM_QUAD_BUFFERS];
};

#endif // FRAMEBUFFERSHADER_H
