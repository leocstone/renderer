#ifndef COLLIDER_H
#define COLLIDER_H
#include <glm/glm.hpp>

using glm::vec3;

struct IntersectData
{
    IntersectData(float dist, bool i) : intersectDistance(dist), intersects(i) {}
    float intersectDistance;
    bool intersects;
};

class Collider
{
public:
    Collider() {}
    virtual ~Collider() {}

    IntersectData collide(Collider& other);

protected:

};

#endif // COLLIDER_H
