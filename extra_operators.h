#ifndef EXTRA_OPERATORS_H
#define EXTRA_OPERATORS_H

#include <glm/glm.hpp>
#include <iostream>
#include <vector>

using glm::vec2;
using glm::vec3;

using std::cout;
using std::endl;
using std::ostream;
using std::vector;

/*

Operator overloads for debug printing

*/
inline vec3 operator*(const vec3& lhs, const double& rhs)
{
    return vec3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

inline ostream& operator<<(ostream& os, const vec3& v)
{
    return os << "( " << v.x << " " << v.y << " " << v.z << " )";
}

inline ostream& operator<<(ostream& os, const vec2& v)
{
    return os << "( " << v.x << " " << v.y << " )";
}

inline ostream& operator<<(ostream& os, const glm::mat4& m)
{
    return os << m[0][0] << " " << m[1][0] << " " << m[2][0] << " " << m[3][0] << endl
              << m[0][1] << " " << m[1][1] << " " << m[2][1] << " " << m[3][1] << endl
              << m[0][2] << " " << m[1][2] << " " << m[2][2] << " " << m[3][2] << endl
              << m[0][3] << " " << m[1][3] << " " << m[2][3] << " " << m[3][3];
}

template<typename T>
inline ostream& operator<<(ostream& os, const vector<T>& v)
{
    for(unsigned i = 0; i < v.size(); i++)
    {
        os << v[i] << " ";
    }
    return os;
}

#endif
