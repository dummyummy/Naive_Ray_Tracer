#include "Scene.h"
#include "Ray.h"
#include "Light.h"
#include "Vector.h"
#include "Surface.h"
#include <vector>
#include <cmath>
#include <algorithm>

void Scene::addObject(Surface *object)
{
    objects.push_back(object);
}

void Scene::addLight(Light *light)
{
    lights.push_back(light);
}

bool Scene::hit(const Ray &ray, const double &T0, const double &T1, HitRecord &hitRecord) const
{
    bool hit = false;
    double t0 = T0, t1 = T1;
    Point3d hitPos;
    Surface *hitObject = nullptr;
    for (auto object : objects)
    {
        if (object->hit(ray, t0, t1, hitPos))
        {
            hit = true;
            hitObject = object;
        }
    }
    if (hit)
    {
        hitRecord.t = t1;
        hitRecord.kd = hitObject->meta->kd;
        hitRecord.km = hitObject->meta->km;
        hitRecord.ks = hitObject->meta->ks;
        hitRecord.p = hitObject->meta->p;
        hitRecord.ka = hitObject->meta->ka;
        hitRecord.n = hitObject->getNormal(hitPos).normalized();
        return true;
    }
    else
        return false;
}

Color3d Scene::rayColor(const Ray &ray, const double &t0, const double &t1, int count) const
{
    HitRecord rec, srec;
    if (count && hit(ray, t0, t1, rec))
    {
        Point3d pos = ray.o + rec.t * ray.d;
        Color3d c = rec.ka * Ia;
        for (auto light : lights)
        {
            Vector3d l = (light->o - pos).normalized();
            if (!hit(Ray(pos, l), 1e-9, 1e18, srec))
            {
                Vector3d h = (l - ray.d.normalized()).normalized();
                c += rec.kd * light->intensity * std::max(0.0, rec.n.dot(l)) + rec.ks * light->intensity * pow(std::max(0.0, rec.n.dot(h)), rec.p);
            }
        }
        Vector3d r = ray.d - 2 * ray.d.dot(rec.n) * rec.n;
        return c + rec.km * rayColor(Ray(pos, r), 1e-9, 1e18, count - 1);
    }
    else
        return background;
}