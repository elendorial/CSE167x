#ifndef __WORLD__
#define __WORLD__

#include "ViewPlane.h"
#include "RGBColor.h"
#include "FreeImage.h"
#include <vector>
#include "GeometricObject.h"
#include "Ray.h"
#include "Whitted.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Pinhole.h"
#include "Light.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>




class World {

    public:

        ViewPlane vp;
        RGBColor background_color;
        Tracer* tracer_ptr;
        std::vector<GeometricObject*> objects;
        std::vector<Point3D> vertices;
        std::vector<Light*> lights;
        Camera* camera_ptr;

    public:

        World(void);

        ~World();

        void build(const char* filename);

        void add_object(GeometricObject* object_ptr);

        void add_light(Light* light_ptr);

        void display_pixel(const int row, const int column, RGBColor& pixel_color) const;

        RGBColor max_to_one(const RGBColor& c) const;

        RGBColor clamp_to_color(const RGBColor& c) const;

        void set_camera(Camera* cam);

        ShadeRec hit_objects(const Ray& ray);

        bool readvals(std::stringstream &s, const int numvals, float* values);

        void add_vertex(Point3D& vertex);


};

inline void World::add_vertex(Point3D& vertex) {
    vertices.push_back(vertex);
}

inline void World::add_object(GeometricObject* object_ptr) {
    objects.push_back(object_ptr);
}

inline void World::set_camera(Camera* cam) {
    camera_ptr = cam;
}

inline void World::add_light(Light* light_ptr) {
    lights.push_back(light_ptr);
}

#endif