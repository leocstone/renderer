#include "objloader.h"

static float correctY(float y)
{
    return fabs(1.0f - y);
}

MeshData OBJLoader::loadOBJ(const string& filename)
{
    MeshData result;
    vector<vec3> vertices;
    vector<vec3> normals;
    vector<vec2> texCoords;

    string currentLine = "";
    ifstream if_stream(filename.c_str());
    while(if_stream.good())
    {
        Vertex v;
        getline(if_stream, currentLine);
        if(currentLine.length() == 0)
        {
            continue;
        }
        switch(currentLine[0])
        {
        case 'v':
            if(currentLine[1] == 'n')
            {
//                cout << "Normal line: ";
                normals.push_back(parseVec3(currentLine));
            }
            else if(currentLine[1] == 't')
            {
//                cout << "Texcoord line: ";
                texCoords.push_back(parseVec2(currentLine));
                // Correct obj UVs to OpenGL
                // (1.0f should be bottom on y axis)
                texCoords[texCoords.size()-1].y = correctY(texCoords[texCoords.size()-1].y);
            }
            else
            {
                vertices.push_back(parseVec3(currentLine));
//                cout << "Vertex line: ";
            }
            break;
        case 'f':
//            cout << "Index line: ";
            parseIndexLine(currentLine, vertices, normals, texCoords, result);
            break;
        default:
//            cout << "Unhandled line: ";
            break;
        }
//        cout << currentLine << endl;
    }
    assert(result.positions.size() == result.texCoords.size());

    return result;
}

vec3 OBJLoader::parseVec3(const string& line)
{
    vec3 result;

    unsigned i = 0;
    unsigned startPositions[3];
    for(; i < line.length(); i++)
    {
        if(line[i] == ' ')
        {
            i++;
            break;
        }
    }
    // x position
    startPositions[0] = i;
    for(; i < line.length(); i++)
    {
        if(line[i] == ' ')
        {
            i++;
            break;
        }
    }
    // y position
    startPositions[1] = i;
    // set x position
    result.x = strtof(line.substr(startPositions[0], startPositions[1] - startPositions[0]).c_str(), 0);
    for(; i < line.length(); i++)
    {
        if(line[i] == ' ')
        {
            i++;
            break;
        }
    }
    // z position
    startPositions[2] = i;
    // set y position
    result.y = strtof(line.substr(startPositions[1], startPositions[2] - startPositions[1]).c_str(), 0);

    // set z position
    result.z = strtof(line.substr(startPositions[2], 8).c_str(), 0);

    return result;
}

vec2 OBJLoader::parseVec2(const string& line)
{
    vec2 result;

    unsigned i = 0;
    unsigned startPositions[3];
    for(; i < line.length(); i++)
    {
        if(line[i] == ' ')
        {
            i++;
            break;
        }
    }
    // x position
    startPositions[0] = i;
    for(; i < line.length(); i++)
    {
        if(line[i] == ' ')
        {
            i++;
            break;
        }
    }
    // y position
    startPositions[1] = i;
    // set x position
    result.x = strtof(line.substr(startPositions[0], startPositions[1] - startPositions[0]).c_str(), 0);
    for(; i < line.length(); i++)
    {
        if(line[i] == ' ')
        {
            i++;
            break;
        }
    }
    // z position
    startPositions[2] = i;
    // set y position
    result.y = strtof(line.substr(startPositions[1], startPositions[2] - startPositions[1]).c_str(), 0);

    return result;
}

struct OBJIndex
{
    OBJIndex(unsigned p, unsigned t, unsigned n) : pos(p), tex(t), nor(n) {}
    OBJIndex(const string& s)
    {
//        cout << "Parsing " << s << " into index:" << endl;
        unsigned indices[3];
        unsigned i = 0;
        for(unsigned j = 0; j < 3; j++)
        {
            unsigned start = i;
            for(; i < s.length(); i++)
            {
                if(s[i] == '/')
                {
                    i++;
                    string current = s.substr(start, i - start - 1);
//                    cout << "From string: " << current << " (Created from " << start << " to " << i-start-1 << ")" << endl;
                    indices[j] = unsigned(atoi(current.c_str()));
                    break;
                }
                else if(i >= s.length() - 1)
                {
                    indices[j] = unsigned(atoi(s.substr(start, s.length()).c_str()));
                    break;
                }
            }
        }
        pos = indices[0] - 1;
        tex = indices[1] - 1;
        nor = indices[2] - 1;
//        cout << pos << endl;
//        cout << tex << endl;
//        cout << nor << endl;
    }
    ~OBJIndex() {}

    unsigned pos;
    unsigned tex;
    unsigned nor;
};

void OBJLoader::parseIndexLine(const string& line, vector<vec3>& pos, vector<vec3>& nor, vector<vec2>& tx, MeshData& m)
{
    unsigned i = 0;
    for(; i < line.length(); i++)
    {
        if(line[i] == ' ')
        {
            i++;
            break;
        }
    }
    vector<string> indices;
    unsigned start = 0;
    for(; i < line.length(); i++)
    {
        string currentIndex;
        start = i;
        for(; i < line.length(); i++)
        {
            if(line[i] == ' ')
            {
                currentIndex = line.substr(start, i - start);
                break;
            }
            else if(i >= line.length() - 1)
            {
                currentIndex = line.substr(start, line.length());
                break;
            }
        }
        indices.push_back(currentIndex);
    }

    // Adding creating indices
    vector<OBJIndex> objIndices;
    for(unsigned j = 0; j < indices.size(); j++)
    {
        objIndices.push_back(OBJIndex(indices[j]));
    }


    if(objIndices.size() == 3)
    {
        // Adding indices to meshdata
        for(unsigned j = 0; j < objIndices.size(); j++)
        {
//            cout << "pos.size() = " << pos.size() << ", accessing " << objIndices[j].pos << endl;
//            cout << "tx.size() = " << tx.size() << ", accessing " << objIndices[j].tex << endl;
//            cout << "nor.size() = " << nor.size() << ", accessing " << objIndices[j].nor << endl;
            m.positions.push_back(pos[objIndices[j].pos]);
            m.texCoords.push_back(tx[objIndices[j].tex]);
            m.normals.push_back(nor[objIndices[j].nor]);
            m.indices.push_back(m.indices.size());
        }
    }
    else if(objIndices.size() == 4)
    {
        // First tri
        for(unsigned j = 0; j < 3; j++)
        {
            m.positions.push_back(pos[objIndices[j].pos]);
            m.texCoords.push_back(tx[objIndices[j].tex]);
            m.normals.push_back(nor[objIndices[j].nor]);
            m.indices.push_back(m.indices.size());
        }
        // Second
        m.positions.push_back(pos[objIndices[0].pos]);
        m.texCoords.push_back(tx[objIndices[0].tex]);
        m.normals.push_back(nor[objIndices[0].nor]);
        m.indices.push_back(m.indices.size());

        m.positions.push_back(pos[objIndices[2].pos]);
        m.texCoords.push_back(tx[objIndices[2].tex]);
        m.normals.push_back(nor[objIndices[2].nor]);
        m.indices.push_back(m.indices.size());

        m.positions.push_back(pos[objIndices[3].pos]);
        m.texCoords.push_back(tx[objIndices[3].tex]);
        m.normals.push_back(nor[objIndices[3].nor]);
        m.indices.push_back(m.indices.size());
    }
    else
    {
//        cout << "Ignoring face that is not tri or quad" << endl;
    }
}

