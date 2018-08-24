#ifndef SHADER_H
#define SHADER_H
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <string>
#include "transform.h"

using std::string;
using std::ifstream;

/*

Shader

Creates, compiles, and manages an OpenGL shader from source files.
Used as a base class for any OpenGL shader.

*/
class Shader
{
public:
    Shader() {}
    virtual ~Shader() {}

    void bind();
    virtual void update(Transform* t) {}
    static string loadShader(const string& fileName);
    static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage);
    static GLuint createShader(const string& text, GLenum shaderType);

protected:
    GLuint m_program;
};

#endif // SHADER_H
