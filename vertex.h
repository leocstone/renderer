#ifndef VERTEX_H
#define VERTEX_H
#include <glm/glm.hpp>

using glm::vec3;
using glm::vec2;

/*

Vertex

Holds data for one vertex in a mesh

*/
class Vertex
{
public:
    Vertex(const vec3 pos = vec3(0, 0, 0), const vec2 texCoord = vec2(0, 0), const vec3 normal = vec3(0, 0, 0))
    {
        m_pos = pos;
        m_texCoord = texCoord;
        m_normal = normal;
    }

    Vertex(const Vertex& v);

    vec3* getPos() { return &m_pos; }
    vec2* getTexCoord() { return &m_texCoord; }
    vec3* getNormal() { return &m_normal; }

    void setPos(const vec3& pos) { m_pos = pos; }
    void setTexCoord(const vec2& texCoord) { m_texCoord = texCoord; }
    void setNormal(const vec3& normal) { m_normal = normal; }

    virtual ~Vertex() {}
private:
    vec3 m_pos;
    vec2 m_texCoord;
    vec3 m_normal;
};

#endif // VERTEX_H
