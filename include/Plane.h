#ifndef PLANE_H
#define PLANE_H

#include "Surface.h"
#include "Ray.h"
#include "Vector.h"

class Plane : public Surface
{
private:
    Point3d base;
    Vector3d normal;

public:
    Plane() = default;
    Plane(const Point3d &base, const Vector3d &normal) : base(base), normal(normal) {}
    Plane(const Point3d &p1, const Point3d &p2, const Point3d &p3);
    void setBase(const Point3d &base);
    void setNormal(const Vector3d &normal);
    Point3d getBase() const;
    Vector3d getNormal() const;
    Vector3d getNormal(const Point3d &point) const;
    bool hit(const Ray &ray, double t0, double &t1, Point3d &pos) const;
};

#endif