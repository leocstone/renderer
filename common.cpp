#include "common.h"

// Interpolation functions
float common::lerp(float current, float target, float step)
{
    return current + ((target - current) * step);
}

float common::lerp_dt(float current, float target)
{
    return lerp(current, target, delta_time);
}

float common::lerp_for(float current, float target, float timeElapsed, float totalTime)
{
    return lerp(current, target, timeElapsed / totalTime);
}

vec3 common::lerpv(const vec3& current, const vec3& target, float step)
{
    return vec3(lerp(current.x, target.x, step), lerp(current.y, target.y, step), lerp(current.z, target.z, step));
}
