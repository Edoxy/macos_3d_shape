#include <iostream>
#include "headers/camera.hpp"
#include <math.h>
#include <vector>

using namespace std;

Camera::Camera(Point3d p)
{
    position = p;
    normal = Point3d(1, 0, 0);
}

Camera::Camera(const Camera &c)
{
    position = c.position;
    normal = c.normal;
}

Camera::~Camera()
{
    this->reset();
}

void Camera::rotate(Point3d p)
{
    normal = p;
    p.to_versor();
}

void Camera::reset()
{
    for (size_t i = 0; i < light_paths.size(); i++)
    {
        delete light_paths[i];
    }

    for (size_t i = 0; i < view.size(); i++)
    {
        delete view[i];
    }
    light_paths.clear();
    view.clear();
    if (plane != NULL)
    {
        delete plane;
        plane = NULL;
    }
}

void Camera::compute_light_path(const Mesh3d &mesh)
{
    const unsigned int n = mesh.get_n_points();

    for (int i = 0; i < n; i++)
    {
        Point3d t = *mesh.get_point(i);
        //add a ray passing form point t and the position of the camera
        light_paths.push_back(new Ray(t, position, true));
    }
}

//compute the plane were the image is projected
void Camera::compute_plane()
{
    if (plane != NULL)
    {
        delete plane;
        plane = NULL;
    }
    //set origin of the plane
    Point3d P_plane = position + normal;
    plane = new Plane(normal, P_plane);

    //caluculate the orientation of the plane
    double inv_x = 0;
    double inv_y = 0;
    if (normal.get_x() != 0 && normal.get_y() != 0)
    {
        inv_x = 1 / normal.get_x();
        inv_y = -1 / normal.get_y();
    }
    else
    {
        inv_x = normal.get_y();
        inv_y = -normal.get_x();
    }
    oriz = Point3d(inv_x, inv_y, 0);
    vert = oriz.x_vect(normal);

    if (vert.get_z() < 0)
    {
        oriz = vert.x_vect(normal);
        vert = oriz.x_vect(normal);
    }

    // if (oriz.get_z() < 0)
    // {
    //     vert = Point3d(-1, (normal.get_x() / normal.get_y()), 0);
    //     oriz = vert.x_vect(normal);
    // }
    vert.to_versor();
    oriz.to_versor();
}

void Camera::compute_view()
{
    for (size_t i = 0; i < light_paths.size(); i++)
    {
        const Ray c_ray = *light_paths[i];
        Point3d *d = plane->compute_intersection(c_ray);
        //check if the intersection exists
        if (d == NULL)
        {
            delete d;
            continue;
        }

        Point3d c = plane->get_point();
        Point3d p = (*d) - c;
        delete d;

        double nx = (p)*oriz;
        double ny = (p)*vert;
        //check if the point is in the field of view
        if (abs(nx) < 0.5 && abs(ny) < 0.5)
        {
            nx = nx + 0.5;
            ny = ny + 0.5;

            view.push_back(new Point2d(nx, ny));
        }
    }
}

Ray *Camera::get_light_path(int i) const
{
    if (i >= light_paths.size())
    {
        cout << "ERROR!: Out of index point" << endl;
        //Return a reference to a NULL pointer
        return NULL;
    }
    else
    {
        return light_paths[i];
    }
}

Point2d *Camera::get_view(int i) const
{
    if (i >= view.size())
    {
        cout << "ERROR!: Out of index point" << endl;
        //Return a reference to a Null pointer
        return NULL;
    }
    else
    {
        return view[i];
    }
}

void Camera::push_view(Point2d *point)
{
    if (point != NULL)
    {
        view.push_back(point);
    }
    return;
}

void Camera::compute_obj_view(const Object &obj)
{
    // check intersection for all the ray that pass from a pixel
    const double step = 1 / double(resolution);
    for (int i = 0; i < resolution; i++)
    {
        for (int j = 0; j < resolution; j++)
        {
            //punto nel piano bidimensionale centrato sulle x e y
            double x_i = i * step;
            double y_i = j * step;
            Point3d p(x_i - 0.5, y_i - 0.5, 0);
            //rotazione
            p.matrix_transorm(oriz, vert, normal);
            // cout << "oriz:" << oriz.tostring() << endl;
            // cout << "vert:" << vert.tostring() << endl;
            // cout << "norm:" << normal.tostring() << endl;
            // traslazione davanti alla camera
            p = p + position + normal;
            //cout << p.tostring() << endl;
            Ray r(p, position, true);
            //cout << r.tostring() << endl;
            double d = obj.intersect(r);
            if (!isnan(d))
            {
                //Punto di intersezione
                Point3d p_int = r.get_from_distance(d);
                //cout << p_int.tostring() << endl;
                Point3d p_normal = obj.normal(p_int);
                Point3d light(1, 0, 1);
                light.to_versor();
                double light_value = light * p_normal;
                view.push_back(new Point2d(x_i, y_i, light_value));
            }
        }
    }
}

void Camera::compute_scene_view(const Scene &scene)
{
    // check intersection for all the ray that pass from a pixel
    const double step = 1 / double(resolution);
    for (int i = 0; i < resolution; i++)
    {
        for (int j = 0; j < resolution; j++)
        {
            //punto nel piano bidimensionale centrato sulle x e y
            double x_i = i * step;
            double y_i = j * step;
            Point3d p(x_i - 0.5, y_i - 0.5, 0);
            //rotazione
            p.matrix_transorm(oriz, vert, normal);
            // cout << "oriz:" << oriz.tostring() << endl;
            // cout << "vert:" << vert.tostring() << endl;
            // cout << "norm:" << normal.tostring() << endl;
            // traslazione davanti alla camera
            p = p + position + normal;
            //cout << p.tostring() << endl;
            Ray r(p, position, true);
            //cout << r.tostring() << endl;
            double d_min = 10000;
            int index = NAN;
            for (int n = 0; n < scene.get_n_obj(); n++)
            {
                Object *obj = scene.get_obj(n);
                double d = obj->intersect(r);
                if (!isnan(d) && abs(d) < abs(d_min))
                {
                    d_min = d;
                    index = n;
                }
            }
            if (d_min != 10000)
            { //Punto di intersezione
                Point3d p_int = r.get_from_distance(d_min);
                //cout << p_int.tostring() << endl;
                Point3d p_normal = scene.get_obj(index)->normal(p_int);
                Point3d light(0, 1, 0);
                light.to_versor();
                double light_value = light * p_normal;
                view.push_back(new Point2d(x_i, y_i, light_value));
            }
        }
    }
}