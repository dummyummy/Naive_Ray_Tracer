#ifndef SPHERE_H
#define SPHERE_H

#include "Surface.h"
#include "Ray.h"
#include "Vector.h"

class Sphere : public Surface
{
private:
    Point3d center;
    double radius;

public:
    Sphere() = default;
    Sphere(const Point3d &center, const double &radius) : center(center), radius(radius) {}
    void setCenter(const Point3d &center);
    void setRadius(const double &radius);
    Point3d getCenter() const;
    double getRadius() const;
    Vector3d getNormal(const Point3d &point) const;
    bool hit(const Ray &ray, double t0, double &t1, Point3d &pos) const;
};

#endif