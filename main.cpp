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
    // scene.add_obj(new Sphere(Point3d(0, 0, 0), 1));
    // scene.add_obj(new Sphere(Point3d(-1, 1, 0), 0.1));
    // scene.add_obj(new Sphere(Point3d(2, 1.5, 0), 0.2));
    // scene.add_obj(new Sphere(Point3d(3, -5, 0), 0.4));
    // scene.add_obj(new Sphere(Point3d(-6, 5, 0), 0.3));
    // scene.add_obj(new Square(Point3d(0, 0, -1), 10));

    //scena Pianeti
    const float r_mercury = 1.2;
    const float r_venus = 1.7;
    const float r_earth = 2.3;
    const float r_mars = 2.9;
    const float r_jupiter = 4;
    const float r_moon = 0.4;

    const Point3d origin(0, 0, 0);
    Sphere sun(origin, 1);
    Sphere mercury(origin, 0.1);
    Sphere venus(origin, 0.13);
    Sphere earth(origin, 0.2);
    Sphere mars(origin, 0.18);
    Sphere jupiter(origin, 0.4);
    Sphere moon(origin, 0.1);

    scene.add_obj(&sun);
    scene.add_obj(&mercury);
    scene.add_obj(&venus);
    scene.add_obj(&earth);
    scene.add_obj(&mars);
    scene.add_obj(&jupiter);
    scene.add_obj(&moon);
    scene.add_obj(new Square(Point3d(0, 0, -1), 10));

    // Ray r(Point3d(0, 0,0), Point3d(2,0,0), true);
    // double intersection = c.intersect(r);
    // cout << intersection;
    float radius = 6;
    Camera cam(Point3d(radius, 0, 5));
    Ray tmp(cam.get_position(), origin, true);
    Point3d dir = tmp.get_tan();
    cam.rotate(dir);
    Display display;
    float t = 0;
    while (t < 20 * 6.28)
    {
        printf("\e[2j\e[H");

        display.clear();

        Point3d pos(-radius * sin(t * 0.2), radius * cos(t * 0.2), 5);
        Ray tmp(pos, origin, true);
        Point3d dir = tmp.get_tan();
        cam.move(pos);
        cam.rotate(dir);
        mercury.set_pos(Point3d(r_mercury * cos(t * 4.15), r_mercury * sin(t * 4.15), 0));
        venus.set_pos(Point3d(r_venus * cos(t * 1.63), r_venus * sin(t * 1.63), 0));
        earth.set_pos(Point3d(r_earth * cos(t), r_earth * sin(t), 0));
        mars.set_pos(Point3d(r_mars * cos(t * 0.531), r_mars * sin(t * 0.531), 0));
        jupiter.set_pos(Point3d(r_jupiter * cos(t * 0.08), r_jupiter * sin(t * 0.08), 0));
        moon.set_pos(Point3d(r_moon * cos(t * 13), r_moon * sin(t * 13), 0) + earth.get_pos());

        cam.reset();
        cam.compute_plane();
        cam.compute_scene_view(scene);
        display.draw(cam);

        t += 0.02;
    }
    return 0;
}