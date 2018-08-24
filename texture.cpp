#include "texture.h"

Texture::Texture()
{
    /// Do nothing
}

Texture::Texture(const std::string& fileName)
{
    int width, height, numComponents;
    unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

    if(imageData == NULL)
        std::cout << "Texture loading failed for texture: " << fileName << std::endl;

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //set texture filtering to linear
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //set texture filtering to none
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    stbi_image_free(imageData);
}

Texture::Texture(byte* ptr, int width, int height, bool shouldDelete)
{
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //set texture filtering to linear
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //set texture filtering to none
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ptr);

    if(shouldDelete)
    {
        delete[] ptr;
    }
}

void Texture::free()
{
    glDeleteTextures(1, &m_texture);
}

Texture::~Texture()
{

}

void Texture::bind(unsigned id)
{
    /*
    Make sure the texture is within the vaild OpenGL
    texture range (0 to 31)
    */
    if(!(id >= 0 && id <= 31))
    {
        std::cout << "ERROR: Tried to bind a texture to id " << id << std::endl;
        return;
    }

    glActiveTexture(GL_TEXTURE0 + id);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}
