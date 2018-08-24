#include "shader.h"

void Shader::bind()
{
    glUseProgram(m_program);
}

/// Create a shader of the given type, upload it to the GPU, attempt to compile it, and then check if it compiled successfully
GLuint Shader::createShader(const string& text, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);

    if(shader == 0)
        cout << "Error: Shader creation failed!" << endl;

    const GLchar* shaderSourceStrings[1];
    GLint shaderSourceStringLengths[1];

    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringLengths[0] = text.length();

    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
    glCompileShader(shader);

    checkShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed");

    return shader;
}

/// Load a text file into a string and return it
string Shader::loadShader(const string& fileName)
{
    ifstream if_stream;
    if_stream.open(fileName.c_str());

    string output;
    string line;

    if(if_stream.is_open())
    {
        while(if_stream.good())
        {
            getline(if_stream, line);
            output.append(line + "\n");
        }
    }
    else
    {
        cout << "Unable to load shader: " << fileName << endl;
    }
    return output;
}

/// Check the OpenGL compile log of a given shader and print it to stdout
void Shader::checkShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        cout << errorMessage << ": '" << error << "'" << endl;
    }
}
