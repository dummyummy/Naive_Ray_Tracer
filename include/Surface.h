#ifndef SURFACE_H
#define SURFACE_H

#include "Vector.h"
#include "Ray.h"
#include "Material.h"

/**
 * base class for 3D surfaces 
 * hit function is implemented in derived classes
 */
class Surface
{
public:
    Material *meta;
    Surface &setMaterial(const Color3d &kd, const double &ks, const double &ka, const double &p, const double &km);
    /**
     * return the surface normal of a point on the surface
     */
    virtual Vector3d getNormal(const Point3d &point) const = 0;
    virtual bool hit(const Ray &ray, double t0, double &t1, Point3d &pos) const = 0;
    virtual ~Surface() {}
};

#endif