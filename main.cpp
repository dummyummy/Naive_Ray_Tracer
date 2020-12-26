#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <cmath>
#include "Vector.h"
#include "Light.h"
#include "Sphere.h"
#include "Plane.h"
#include "Ray.h"
#include "svpng.h"
#include "Scene.h"

using namespace std;

const int width = 600, height = 600, channels = 3;
Vector3d window[height][width];
byte img[width * height * channels];

int main()
{
    Point3d eyePos(0, 300, 2000), lightPos(300, 300, 800);
    int R = (int)eyePos.x + width / 2, U = (int)eyePos.y + height / 2;
    int L = (int)eyePos.x - width / 2, B = (int)eyePos.y - height / 2;
    Scene scene(Color3d(0, 0, 0), Color3d(30, 30, 30));
    scene.addObject(&(new Plane(Point3d(0, 0, 0), Vector3d(0, 1, 0)))->setMaterial(Color3d(0.3, 0.3, 0.3), 0, 0.1, 0, 0.5));
    scene.addObject(&(new Sphere(Point3d(-100, 50, -500), 50))->setMaterial(Color3d(0, 0.3, 0), 0.2, 0.1, 75, 0.4));
    scene.addObject(&(new Sphere(Point3d(100, 100, -1000), 100))->setMaterial(Color3d(0.3, 0, 0), 0.2, 0.1, 75, 0.4));
    scene.addLight(new Light(lightPos, Color3d(500, 500, 500)));
    // scene.addLight(new Light(Point3d(-300, 200, 400), Color3d(300, 300, 300)));
    for (int i = 0; i < width; ++i)
    {
        #pragma omp parallel for
        for (int j = 0; j < height; ++j)
        {
            Point3d pixelPos(L + i + 0.5, B + j + 0.5, 0);
            Ray ray(pixelPos, (pixelPos - eyePos).normalized());
            window[height - 1 - j][i] = scene.rayColor(ray, 0, 1e18);
        }
    }
    byte *p1 = img;
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            *p1 = (byte)min(255.0, window[i][j].r);
            p1++;
            *p1 = (byte)min(255.0, window[i][j].g);
            p1++;
            *p1 = (byte)min(255.0, window[i][j].b);
            p1++;
        }
    }
    FILE *f = fopen("../ground.png", "wb");
    svpng(f, width, height, img, 0);
    fclose(f);
}