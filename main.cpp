#include <iostream>
#include "headers/point2d.hpp"
#include "headers/point3d.hpp"
#include "headers/ray.hpp"
#include "headers/mesh3d.hpp"
#include "headers/camera.hpp"
#include "headers/display.hpp"
#include <memory>

using namespace std;

struct AllocationMetrics
{
    uint32_t TotalAllocated = 0;
    uint32_t TotalFreed = 0;

    uint32_t CurrentUsage() { return TotalAllocated - TotalFreed; }
};

static AllocationMetrics s_AllocationMetrics;

void *operator new(size_t size)
{
    s_AllocationMetrics.TotalAllocated += size;
    return malloc(size);
}

void operator delete(void *memory, size_t size)
{
    s_AllocationMetrics.TotalFreed += size;
    free(memory);
}

static void PrintMemoryUsage()
{
    std::cout << "Memory Usage: " << (s_AllocationMetrics.CurrentUsage() / 1012) / 1012 << " Mb\n";
}

void TestFunc()
{
    Point3d p1(1, 0, 0);
    Point3d p2(0, 1, 0);
    Point3d p3 = p1 + p2;
    Point3d p4 = p1.x_vect(p2);
    Ray r(p1, p2, false);
    Ray r1(p3, p4, true);
    double dot = p1 * p2;
    p3.to_versor();
    cout << p3.tostring() << endl;
    cout << p4.tostring() << endl;
    cout << dot << endl;
    cout << p3.tostring() << endl;
    cout << r.tostring() << endl;
    cout << r1.tostring() << endl;

    //meshTest
    Mesh3d mesh;
    mesh.add_point(&p1);
    mesh.add_point(&p2);
    cout << mesh.tostring() << endl;
}

int main()
{

    fputs("\e[?25l", stdout);
    Scene scene;
    // Scena Podio
    // scene.add_obj(new Sphere(Point3d(0, 0, 1), 0.5));
    // scene.add_obj(new Sphere(Point3d(1, 0, 0), 0.5));
    // scene.add_obj(new Cube(Point3d(0, 0, 0), 0.5));
    // scene.add_obj(new Cube(Point3d(0, 0, -1), 0.5));
    // scene.add_obj(new Cube(Point3d(1, 0, -1), 0.5));
    // scene.add_obj(new Sphere(Point3d(-1, 0, -1), 0.5));
    // scene.add_obj(new Square(Point3d(0, 0, -1.5), 5));

    //Scena Semplice dimostrazione luci e piano
    scene.add_obj(new Sphere(Point3d(0, 0, 0.5), 0.5));
    scene.add_obj(new Sphere(Point3d(-2, 2, 2), 0.2));
    scene.add_obj(new Sphere(Point3d(-1, 1, 2), 0.3));
    scene.add_obj(new Cube(Point3d(1, 0, 0.5), 0.5));
    scene.add_obj(new Square(Point3d(0, 0, 0), 3));
    



    // Ray r(Point3d(0, 0,0), Point3d(2,0,0), true);
    // double intersection = c.intersect(r);
    // cout << intersection;
    float radius = 5;
    Camera cam(Point3d(radius, 0, 0));
    Display display;
    float t = 0;
    while (t < 2 * 6.28)
    {
        printf("\e[2j\e[H");

        display.clear();

        Point3d pos(-radius * sin(t), radius * cos(t), 3);

        Ray tmp(pos, Point3d(0, 0, 0), true);
        Point3d dir = tmp.get_tan();

        cam.move(pos);

        cam.rotate(dir);

        Display display;
        cam.reset();
        cam.compute_plane();
        cam.compute_scene_view(scene);
        display.draw(cam);

        t += 0.03;
    }
    return 0;
}