#include "Plane.h"
#include "Vector.h"

Plane::Plane(const Point3d &p1, const Point3d &p2, const Point3d &p3)
{
    base = p1;
    normal = (p1 - p2).cross(p3 - p1);
}

void Plane::setBase(const Point3d &base)
{
    this->base = base;
}

void Plane::setNormal(const Vector3d &normal)
{
    this->normal = normal;
}

Point3d Plane::getBase() const
{
    return base;
}

Vector3d Plane::getNormal() const
{
    return normal;
}

Vector3d Plane::getNormal(const Point3d &point) const
{
    return normal;
}

/**
 * return true when the ray hits surface
 * @param ray the ray to be checked
 * @param t0 record only when t0 <= t <= t1
 * @param t1 record only when t0 <= t <= t1
 * @param pos restores the position where hit takes place
 */
bool Plane::hit(const Ray &ray, double t0, double &t1, Point3d &pos) const
{
    Vector3d o = ray.o, d = ray.d;
    double nd = normal.dot(d);
    if (nd >= -1e-9 && nd <= 1e-9)
        return false;
    double t = normal.dot(base - o) / nd;
    if (t < t0 || t > t1)
        return false;
    t1 = t;
    pos = o + t * d;
    return true;
}