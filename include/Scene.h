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
        Color3d kd, km;
        double ks, p, ka;
        Vector3d n;
        HitRecord() = default;
        ~HitRecord() = default;
        HitRecord(const double &t, const Color3d &kd, const Color3d &km, const double &ks, const double &p, const double &ka, const Vector3d &n) : t(t), kd(kd), km(km), ks(ks), p(p), ka(ka), n(n) {}
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
    Color3d rayColor(const Ray &ray, const double &t0, const double &t1, int count = 1000) const;
};

#endif