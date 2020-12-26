#include "Sphere.h"
#include "Vector.h"

void Sphere::setCenter(const Point3d &center)
{
    this->center = center;
}

void Sphere::setRadius(const double &radius)
{
    this->radius = radius;
}

Point3d Sphere::getCenter() const
{
    return center;
}

double Sphere::getRadius() const
{
    return radius;
}

Vector3d Sphere::getNormal(const Point3d &point) const
{
    return (point - center) / radius;
}

/**
 * return true when the ray hits surface
 * @param ray the ray to be checked
 * @param t0 record only when t0 <= t <= t1
 * @param t1 record only when t0 <= t <= t1
 * @param pos restores the position where hit takes place
 */
bool Sphere::hit(const Ray &ray, double t0, double &t1, Point3d &pos) const
{
    Vector3d o = ray.o, d = ray.d;
    Vector3d c2o = o - center;
    double d_dot_c2o = d.dot(c2o), d2 = d.dot(d);
    double det = d_dot_c2o * d_dot_c2o - d2 * (c2o.dot(c2o) - radius * radius);
    if (det < 0)
        return false;
    double sqr = sqrt(det);
    double x0 = -d_dot_c2o - sqr, rhs0 = t0 * d2, rhs1 = t1 * d2;
    if (x0 < rhs0 || x0 > rhs1)
    {
        double x1 = -d_dot_c2o + sqr;
        if (x1 < rhs0 || x1 > rhs1)
            return false;
        else
        {
            x1 /= d2;
            t1 = x1;
            pos = o + x1 * d;
            return true;
        }
    }
    else
    {
        x0 /= d2;
        t1 = x0;
        pos = o + x0 * d;
        return true;
    }
}