#include "unlitshader.h"

UnlitShader::UnlitShader(const string& fileName, Camera* c)
{
    m_program = glCreateProgram();
    m_shaders[0] = createShader(loadShader(fileName + ".vs"), GL_VERTEX_SHADER);
    m_shaders[1] = createShader(loadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

    for(unsigned i = 0; i < NUM_SHADERS; i++)
        glAttachShader(m_program, m_shaders[i]);

    glBindAttribLocation(m_program, 0, "position");
    glBindAttribLocation(m_program, 1, "texCoord");
    glBindAttribLocation(m_program, 2, "normal");

    glLinkProgram(m_program);
    checkShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed");

    glValidateProgram(m_program);
    checkShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid");

    m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");

    for(unsigned i = 0; i < NUM_UNIFORMS; i++)
    {
        cout << "Uniform " << i << ": " << m_uniforms[i] << endl;
    }

    m_camera = c;
}

UnlitShader::~UnlitShader()
{
    for(unsigned i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }

    glDeleteProgram(m_program);
}

void UnlitShader::update(Transform* tr)
{
    glm::mat4 transformMat = m_camera->getViewProjection() * tr->getModel();

    glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &transformMat[0][0]);
}
