#include "Surface.h"
#include "Vector.h"

Surface &Surface::setMaterial(const Color3d &kd, const Color3d &km, const double &ks, const double &p, const double &ka)
{
    meta = new Material(kd, km, ks, p, ka);
    return *this;
}