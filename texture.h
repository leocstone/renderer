#ifndef TEXTURE_H
#define TEXTURE_H
#include <GL/glew.h>
#include <iostream>
#include <string>
#include "lib/stb_image.h"

using std::string;
using std::cout;
using std::endl;

typedef unsigned char byte;

/*

Texture

Creates and manages an OpenGL texture from image data.

*/
class Texture
{
public:
    Texture();
    Texture(const Texture& t) { m_texture = t.getID(); }
    Texture(const string& fileName);
    Texture(byte* ptr, int width, int height, bool shouldDelete);

    void bind(unsigned id);
    void free();
    inline GLuint getID() const { return m_texture; }

    virtual ~Texture();
private:
    GLuint m_texture;
    string m_fileName;
};

#endif // TEXTURE_H
