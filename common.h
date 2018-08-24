#ifndef COMMON_H
#define COMMON_H

#include "engine_constants.h"
using glm::vec3;

// Static methods for basic operations - currently just interpolation
class common
{
public:

    static float lerp(float current, float target, float step);
    static float lerp_dt(float current, float target);
    static float lerp_for(float current, float target, float timeElapsed, float totalTime);

    static vec3 lerpv(const vec3& current, const vec3& target, float step);
};

#endif // COMMON_H
