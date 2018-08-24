#ifndef UNLITSHADER_H
#define UNLITSHADER_H

#include "shader.h"
#include "camera.h"

/*

UnlitShader

A very basic shader that just transforms the object and does no lighting calculations

*/
class UnlitShader : public Shader
{
public:
    UnlitShader(const string& fileName, Camera* c);

    void update(Transform* tr);

    ~UnlitShader();
protected:
    // Fragment shader, vertex shader
    static const unsigned NUM_SHADERS = 2;

    enum
    {
        TRANSFORM_U,

        NUM_UNIFORMS
    };

    GLuint m_shaders[NUM_SHADERS];
    GLuint m_uniforms[NUM_UNIFORMS];

    Camera* m_camera;
};

#endif // UNLITSHADER_H
