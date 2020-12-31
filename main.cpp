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
    Point3d eyePos(0, 300, 2000);
    int R = (int)eyePos.x + width / 2, U = (int)eyePos.y + height / 2;
    int L = (int)eyePos.x - width / 2, B = (int)eyePos.y - height / 2;
    Scene scene(Color3d(0, 0, 0), Color3d(30, 30, 30));
    scene.addObject(&(new Plane(Point3d(0, 0, 0), Vector3d(0, 1, 0)))->setMaterial(Color3d(0, 0, 0), Color3d(1, 1, 1), 0, 0, 0));
    // scene.addObject(&(new Sphere(Point3d(-100, 50, -500), 50))->setMaterial(Color3d(0, 0.3, 0), Color3d(0, 0.3, 0), 0.1, 75, 0));
    scene.addObject(&(new Sphere(Point3d(100, 150, -2000), 100))->setMaterial(Color3d(0.3, 0, 0), Color3d(0.3, 0, 0), 0.1, 75, 0));
    // scene.addObject(&(new Sphere(Point3d(80, 80, -100), 70))->setMaterial(Color3d(0.3, 0.3, 0), 0.2, 0.1, 75, 0));
    scene.addLight(new Light(Point3d(-200, 500, -200), Color3d(400, 400, 400)));
    // scene.addLight(new Light(Point3d(1000, 200, -300), Color3d(200, 200, 200)));
    // scene.addLight(new Light(Point3d(-300, 200, 400), Color3d(300, 300, 300)));
    double pos[4][2] = {0.25, 0.25, 0.25, 0.75, 0.75, 0.25, 0.75, 0.75};
    for (int i = 0; i < width; ++i)
    {
        #pragma omp parallel for
        for (int j = 0; j < height; ++j)
        {
            window[height - 1 - j][i] = Vector3d(0, 0, 0);
            for (int k = 0; k < 4; ++k)
            {
                Point3d pixelPos(L + i + pos[k][0], B + j + pos[k][1], 0);
                Ray ray(pixelPos, (pixelPos - eyePos).normalized());
                window[height - 1 - j][i] += scene.rayColor(ray, 0, 1e18);
            }
            window[height - 1 - j][i] /= 4;
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