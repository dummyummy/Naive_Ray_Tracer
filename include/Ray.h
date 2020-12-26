#pragma once

#include "Vector.h"

struct Ray
{
    Point3d o;  // origin
    Vector3d d; // direction
    Ray() = default;
    ~Ray() = default;
    Ray(const Point3d &o, const Vector3d &d) : o(o), d(d) {}
};