#include "meshdata.h"

/**
Note: this function does not perform checks to see if
MeshData already has the same Vertex somewhere else
**/
void MeshData::addVertex(Vertex* v)
{
    positions.push_back(*v->getPos());
    texCoords.push_back(*v->getTexCoord());
    normals.push_back(*v->getNormal());
    indices.push_back(indices.size() - 1);
}

void MeshData::addMeshData(const MeshData& m)
{
    unsigned indicesSize = positions.size();

    for(unsigned i = 0; i < m.positions.size(); i++)
    {
        positions.push_back(m.positions[i]);
    }

    for(unsigned i = 0; i < m.texCoords.size(); i++)
        texCoords.push_back(m.texCoords[i]);

    for(unsigned i = 0; i < m.normals.size(); i++)
        normals.push_back(m.normals[i]);

    for(unsigned i = 0; i < m.indices.size(); i++)
    {
        unsigned current = indicesSize + m.indices[i];
        //cout << "Adding " << current << " ( " << indicesSize << " + " << m.indices[i] << " )" << endl;
        indices.push_back(current);
    }
}

///TODO: This
void MeshData::calculateNormals()
{

}

void MeshData::print()
{
    cout << "Positions: " << endl;
    for(unsigned i = 0; i < positions.size(); i++)
        cout << positions[i] << endl;

    cout << "uvs: " << endl;
    for(unsigned i = 0; i < texCoords.size(); i++)
        cout << texCoords[i] << endl;

    cout << "Normals: " << endl;
    for(unsigned i = 0; i < normals.size(); i++)
        cout << normals[i] << endl;

    cout << "Indices: " << endl;
    for(unsigned i = 0; i < indices.size(); i++)
        cout << indices[i] << endl;
}
