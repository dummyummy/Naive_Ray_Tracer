#ifndef LIGHT_H
#define LIGHT_H

#include "Vector.h"

struct Light
{
    Point3d o;
    Color3d intensity;
    Light() = default;
    ~Light() = default;
    Light(const Point3d &o, const Color3d &intensity) : o(o), intensity(intensity) {}
};

#endif