#ifndef MATERIAL_H
#define MATERIAL_H

#include "Vector.h"

struct Material
{
    Color3d kd;
    double ks, ka, p, km;
    Material() = default;
    ~Material() = default;
    Material(const Color3d &kd, const double &ks, const double &ka, const double &p, const double &km) : kd(kd), ks(ks), ka(ka), p(p), km(km) {}
};

#endif