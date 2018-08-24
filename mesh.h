#ifndef MESH_H
#define MESH_H

#include "meshdata.h"
#include <GL/glew.h>

/*

Mesh

Loads a 3D mesh from a set of vertices or an instance of MeshData, and manages it on the GPU

*/
class Mesh
{
public:
    Mesh();
    Mesh(Vertex* vertices, unsigned numVertices, unsigned* indices, unsigned numIndices);
    Mesh(const MeshData&);

    // Loads mesh data onto gpu and prepares for drawing
    void initMesh();

    // Draws the mesh. This function should be called after binding textures, shaders, etc from a MeshRenderer.
    void draw();
    void print() { m_meshData.print(); }

    void setMeshData(MeshData* m) { m_meshData = *m; }

    virtual ~Mesh();
private:
    MeshData m_meshData;

    enum ComponentVB
    {
        POSITION_VB,
        TEXCOORD_VB,
        NORMAL_VB,

        INDEX_VB,

        NUM_BUFFERS
    };

    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];

    unsigned m_drawCount;
};

#endif // MESH_H
