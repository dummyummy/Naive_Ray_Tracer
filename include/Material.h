#ifndef MATERIAL_H
#define MATERIAL_H

#include "Vector.h"

struct Material
{
    Color3d kd, km;
    double ks, ka, p;
    Material() = default;
    ~Material() = default;
    Material(const Color3d &kd, const Color3d &km, const double &ks, const double &p, const double &ka) : kd(kd), km(km), ks(ks), ka(ka), p(p) {}
};

#endif