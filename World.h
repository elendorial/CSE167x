#ifndef __WORLD__
#define __WORLD__

#include "ViewPlane.h"
#include "RGBColor.h"
#include "FreeImage.h"
#include <vector>
#include "GeometricObject.h"
#include "Ray.h"
#include "MultipleObjects.h"
#include "Plane.h"
#include "Sphere.h"
#include "Pinhole.h"
#include "ThinLens.h"
#include "Fisheye.h"
#include "Spherical.h"


class World {

	public:

		ViewPlane vp;
		RGBColor background_color;
		Tracer* tracer_ptr;
		std::vector<GeometricObject*> objects;
		Sphere sphere;
		Camera* camera_ptr;

	public:

		World(void);

		~World();

		void build(void);

		void add_object(GeometricObject* object_ptr);

		ShadeRec hit_bare_bones_objects(const Ray& ray);

		void render_scene(void) const;

		void open_window(const int hres, const int vres) const;

		void display_pixel(const int row, const int column, RGBColor& pixel_color) const;

		RGBColor max_to_one(const RGBColor& c) const;

		RGBColor clamp_to_color(const RGBColor& c) const;

		void set_camera(Camera* cam);


};

inline void World::add_object(GeometricObject* object_ptr) {
	objects.push_back(object_ptr);
}

inline void World::set_camera(Camera* cam) {
	camera_ptr = cam;
}

#endif