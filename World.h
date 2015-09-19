#ifndef __WORLD__
#define __WORLD__

#include "ViewPlane.h"
#include "RGBColor.h"
#include "FreeImage.h"
#include <vector>
#include "GeometricObject.h"
#include "Ray.h"
#include "MultipleObjects.h"
#include "RayCast.h"
#include "Whitted.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Pinhole.h"
#include "ThinLens.h"
#include "Fisheye.h"
#include "Spherical.h"
#include "Light.h"
#include "Ambient.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>




class World {

	public:

		ViewPlane vp;
		RGBColor background_color;
		Light* ambient_ptr;
		Tracer* tracer_ptr;
		std::vector<GeometricObject*> objects;
		std::vector<Point3D> vertices;
		std::vector<Light*> lights;
		Sphere sphere;
		Camera* camera_ptr;

	public:

		World(void);

		~World();

		void build(const char* filename);

		void add_object(GeometricObject* object_ptr);

		void add_light(Light* light_ptr);

		ShadeRec hit_bare_bones_objects(const Ray& ray);

		void render_scene(void) const;

		void open_window(const int hres, const int vres) const;

		void display_pixel(const int row, const int column, RGBColor& pixel_color) const;

		RGBColor max_to_one(const RGBColor& c) const;

		RGBColor clamp_to_color(const RGBColor& c) const;

		void set_camera(Camera* cam);

		void set_ambient_light(Light* light_ptr);			

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

inline void World::set_ambient_light(Light* light_ptr) {
	ambient_ptr = light_ptr;
}

#endif