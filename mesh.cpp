#include "mesh.h"

Mesh::Mesh()
{
    m_drawCount = 0;
}

/// From meshdata constructor
Mesh::Mesh(const MeshData& m)
{
    m_meshData = m;

    m_drawCount = m_meshData.indices.size();

    initMesh();
    cout << "Passed initmesh" << endl;
}

Mesh::Mesh(Vertex* vertices, unsigned numVertices, unsigned* indices, unsigned numIndices)
{
    for(unsigned i = 0; i < numVertices; i++)
    {
        m_meshData.positions.push_back(*vertices[i].getPos());
        m_meshData.texCoords.push_back(*vertices[i].getTexCoord());
        m_meshData.normals.push_back(*vertices[i].getNormal());
    }

    for(unsigned i = 0; i < numIndices; i++)
    {
        m_meshData.indices.push_back(indices[i]);
    }

    m_drawCount = m_meshData.indices.size();

    initMesh();
}

void Mesh::initMesh()
{
    glGenVertexArrays(1, &m_vertexArrayObject);

    glBindVertexArray(m_vertexArrayObject);

    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, m_meshData.positions.size() * sizeof(m_meshData.positions[0]), &m_meshData.positions[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, m_meshData.texCoords.size() * sizeof(m_meshData.texCoords[0]), &m_meshData.texCoords[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, m_meshData.normals.size() * sizeof(m_meshData.normals[0]), &m_meshData.normals[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_meshData.indices.size() * sizeof(m_meshData.indices[0]), &m_meshData.indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::draw()
{
    glBindVertexArray(m_vertexArrayObject);

    glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}
