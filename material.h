#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include <iostream>

using std::ostream;
using glm::vec3;

/*

Material structs for use as shader uniforms

*/
struct Material
{
    Material() {}
    Material(const vec3& a, const vec3& d, const vec3& s, float sh)
    {
        ambient = a;
        diffuse = d;
        specular = s;
        shininess = sh;
    }

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct MaterialUniforms
{
    unsigned ambient;
    unsigned diffuse;
    unsigned specular;
    unsigned shininess;
};

inline ostream& operator<<(ostream& os, const MaterialUniforms& u)
{
    return os << u.ambient << " " << u.diffuse << " " << u.specular << " " << u.shininess;
}

#endif // MATERIAL_H
