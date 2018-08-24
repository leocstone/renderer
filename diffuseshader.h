#ifndef DIFFUSESHADER_H
#define DIFFUSESHADER_H
#include "shader.h"
#include "light.h"
#include "camera.h"
#include "material.h"

/*

DiffuseShader

Loads the diffuse shader in diffuseShader.fs/.vs and manages its uniforms

*/
class DiffuseShader : public Shader
{
public:

    DiffuseShader() {}
    DiffuseShader(const string& fileName, Camera* c, DirectionalLight* dLight, Material* mat);
    ~DiffuseShader();

    void update(Transform* tr);

private:
    // Fragment shader, vertex shader
    static const unsigned NUM_SHADERS = 2;

    enum
    {
        TRANSFORM_U,
        MODEL_U,
        EYE_U,

        NUM_UNIFORMS
    };

    GLuint m_shaders[NUM_SHADERS];
    GLuint m_uniforms[NUM_UNIFORMS];
    DirectionalLightUniforms m_directionalLightUniforms;
    MaterialUniforms m_materialUniforms;

    Camera* m_camera;

    DirectionalLight* m_directionalLight;
    Material* m_material;
};

#endif // DIFFUSESHADER_H
