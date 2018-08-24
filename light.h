#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

using glm::vec3;

/*

Light structs for use as shader uniforms

*/
struct DirectionalLight
{
    DirectionalLight() {}
    DirectionalLight(const vec3& _direction, const vec3& _ambient, const vec3& _diffuse, const vec3& _specular) : direction(_direction), ambient(_ambient), diffuse(_diffuse), specular(_specular) {}

    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirectionalLightUniforms
{
    unsigned direction;

    unsigned ambient;
    unsigned diffuse;
    unsigned specular;
};

inline ostream& operator<<(ostream& os, const DirectionalLightUniforms& u)
{
    return os << u.direction << " " << u.ambient << " " << u.diffuse << " " << u.specular;
}

struct PointLight
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // Attenuation constants
    float linear;
    float quadratic;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;

    float cutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // Attenuation constants
    float linear;
    float quadratic;
};

#endif // LIGHT_H

