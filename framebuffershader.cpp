#include "framebuffershader.h"

static const float quadPositions[] =
{
    -1.0f,  1.0f,
    -1.0f, -1.0f,
    1.0f, -1.0f,

    -1.0f,  1.0f,
    1.0f, -1.0f,
    1.0f,  1.0f
};

static const float quadTexCoords[] =
{
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f
};

FramebufferShader::FramebufferShader(const string& fileName)
{
    m_program = glCreateProgram();
    m_shaders[0] = createShader(loadShader(fileName + ".vs"), GL_VERTEX_SHADER);
    m_shaders[1] = createShader(loadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

    for(unsigned i = 0; i < NUM_SHADERS; i++)
        glAttachShader(m_program, m_shaders[i]);

    glBindAttribLocation(m_program, 0, "position");
    glBindAttribLocation(m_program, 1, "texCoord");

    glLinkProgram(m_program);
    checkShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed");

    glValidateProgram(m_program);
    checkShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid");

    initQuad();
}

FramebufferShader::~FramebufferShader()
{
    for(unsigned i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }

    glDeleteProgram(m_program);
    glDeleteVertexArrays(1, &m_quadVao);
}

void FramebufferShader::update()
{
    glBindVertexArray(m_quadVao);
    glDrawArrays(GL_TRIANGLES, 0, m_quadDrawCount);
    glBindVertexArray(0);
}

void FramebufferShader::initQuad()
{
    glGenVertexArrays(1, &m_quadVao);
    glBindVertexArray(m_quadVao);

    glGenBuffers(NUM_QUAD_BUFFERS, m_quadBuffers);
    glBindBuffer(GL_ARRAY_BUFFER, m_quadBuffers[QUAD_POSITION]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadPositions), &quadPositions[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_quadBuffers[QUAD_TEXCOORD]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadTexCoords), &quadTexCoords[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
}
