#include "Surface.h"
#include "Vector.h"

Surface &Surface::setMaterial(const Color3d &kd, const double &ks, const double &ka, const double &p, const double &km)
{
    meta = new Material(kd, ks, ka, p, km);
    return *this;
}