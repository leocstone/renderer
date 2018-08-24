#ifndef OBJLOADER_H
#define OBJLOADER_H
#include "meshdata.h"
#include <fstream>
#include <sstream>
#include <string>

using std::string;
using std::stringstream;
using std::ifstream;

// Static class for loading files in OBJ format. Will segfault if given a mesh that has no UVs.
class OBJLoader
{
public:
    OBJLoader() {};
    ~OBJLoader() {};

    static MeshData loadOBJ(const string& filename);
    static vec3 parseVec3(const string& line);
    static vec2 parseVec2(const string& line);
    static void parseIndexLine(const string& line, vector<vec3>& pos, vector<vec3>& nor, vector<vec2>& tx, MeshData& m);
};

#endif // OBJLOADER_H
