#ifndef SCENE_H
#define SCENE_H

#include "Ray.h"
#include "Light.h"
#include "Vector.h"
#include "Surface.h"
#include <vector>

struct Scene
{
    struct HitRecord
    {
        double t;
        Color3d kd;
        double ks, ka, p, km;
        Vector3d n;
        HitRecord() = default;
        ~HitRecord() = default;
        HitRecord(const double &t, const Color3d &kd, const double &ks, const double &ka, const double &p, const double &km, const Vector3d &n) : t(t), kd(kd), ks(ks), ka(ka), p(p), km(km), n(n) {}
    };
    std::vector<Surface *> objects;
    std::vector<Light *> lights;
    Color3d background, Ia;
    Scene() = default;
    ~Scene() = default;
    Scene(const Color3d &background, const Color3d &Ia) : background(background), Ia(Ia) {}
    void addObject(Surface *object);
    void addLight(Light *light);
    bool hit(const Ray &ray, const double &T0, const double &T1, HitRecord &hitRecord) const;
    Color3d rayColor(const Ray &ray, const double &t0, const double &t1) const;
};

#endif