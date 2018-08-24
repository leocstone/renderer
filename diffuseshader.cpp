#include "diffuseshader.h"

DiffuseShader::~DiffuseShader()
{
    for(unsigned i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }
    glDeleteProgram(m_program);
}

DiffuseShader::DiffuseShader(const string& fileName, Camera* c, DirectionalLight* dLight, Material* mat) : m_directionalLight(dLight), m_material(mat)
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
    m_uniforms[MODEL_U] = glGetUniformLocation(m_program, "model");
    m_uniforms[EYE_U] = glGetUniformLocation(m_program, "viewPos");

    m_directionalLightUniforms.direction = glGetUniformLocation(m_program, "directionalLight.direction");
    m_directionalLightUniforms.ambient = glGetUniformLocation(m_program, "directionalLight.ambient");
    m_directionalLightUniforms.diffuse = glGetUniformLocation(m_program, "directionalLight.diffuse");
    m_directionalLightUniforms.specular = glGetUniformLocation(m_program, "directionalLight.specular");

    cout << "Uniforms for diffuseShader: " << endl;
    cout << m_directionalLightUniforms << endl;

    m_materialUniforms.ambient = glGetUniformLocation(m_program, "material.ambient");
    m_materialUniforms.diffuse = glGetUniformLocation(m_program, "material.diffuse");
    m_materialUniforms.specular = glGetUniformLocation(m_program, "material.specular");
    m_materialUniforms.shininess = glGetUniformLocation(m_program, "material.shininess");

    cout << m_materialUniforms << endl;

    for(unsigned i = 0; i < NUM_UNIFORMS; i++)
    {
        cout << "Uniform " << i << ": " << m_uniforms[i] << endl;
    }
    m_camera = c;
}

void DiffuseShader::update(Transform* tr)
{
    glm::mat4 transformMat = m_camera->getViewProjection() * tr->getModel();
    glm::mat4 model = tr->getModel();

    glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &transformMat[0][0]);
    glUniformMatrix4fv(m_uniforms[MODEL_U], 1, GL_FALSE, &model[0][0]);
    glUniform3fv(m_uniforms[EYE_U], 1, &m_camera->position[0]);

    glUniform3fv(m_directionalLightUniforms.direction, 1, &m_directionalLight->direction[0]);
    glUniform3fv(m_directionalLightUniforms.ambient, 1, &m_directionalLight->ambient[0]);
    glUniform3fv(m_directionalLightUniforms.diffuse, 1, &m_directionalLight->diffuse[0]);
    glUniform3fv(m_directionalLightUniforms.specular, 1, &m_directionalLight->specular[0]);

    glUniform3fv(m_materialUniforms.ambient, 1, &m_material->ambient[0]);
    glUniform3fv(m_materialUniforms.diffuse, 1, &m_material->diffuse[0]);
    glUniform3fv(m_materialUniforms.specular, 1, &m_material->specular[0]);
    glUniform1fv(m_materialUniforms.shininess, 1, &m_material->shininess);
}
