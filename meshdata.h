#ifndef MESHDATA_H
#define MESHDATA_H

#include "vertex.h"
#include "extra_operators.h"
#include <iostream>
#include <vector>
#include <GL/glew.h>

using std::vector;
using std::cout;
using std::endl;

/*

MeshData: Class for a mesh while still in RAM

*/
class MeshData
{
public:
    MeshData() {}
    MeshData(const MeshData& m)
    {
        positions = m.positions;
        texCoords = m.texCoords;
        normals = m.normals;
        indices = m.indices;
    }

    void addMeshData(const MeshData& m);
    void addVertex(Vertex* v);

    void calculateNormals();
    void print();

    vector<vec3> positions;
    vector<vec2> texCoords;
    vector<vec3> normals;
    vector<unsigned> indices;

};

#endif // MESHDATA_H
