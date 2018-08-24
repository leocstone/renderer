#include "vertex.h"

Vertex::Vertex(const Vertex& v)
{
    m_pos = v.m_pos;
    m_texCoord = v.m_texCoord;
    m_normal = v.m_normal;
}
