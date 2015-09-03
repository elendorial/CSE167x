#include "World.h"
#include "Constants.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "Normal.h"
#include "Ray.h"


World::World(void)
:	background_color(black),
	tracer_ptr(NULL)
{}

World::~World(void) {
	if(tracer_ptr) {
		delete tracer_ptr;
		tracer_ptr = NULL;
	}
}

void World::render_scene(void) const {
	RGBColor pixel_color;
	Ray ray;
	double zw = 100.0;
	double x, y;

	//open_window(vp.hres, vp.vres);
	ray.d = Vector3D(0, 0, -1);

	for(int r = 0; r < vp.vres; r++)
		for(int c = 0; c <= vp.hres; c++) {
			x = vp.s * (c - 0.5 * (vp.hres - 1.0));
			y = vp.s * (r - 0.5 * (vp.vres - 1.0));
			ray.o = Point3D(x, y, zw);
			pixel_color = tracer_ptr -> trace_ray(ray);
			//display_pixel(r, c, pixel_color);

		}
}

void World::build(void) {
	vp.set_hres(200);
	vp.set_vres(200);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);

	background_color = black;
	tracer_ptr = new SingleSphere(this);

	sphere.set_center(0.0);
	sphere.set_radius(85.0);
}

int main(void)
{
	World w;
	w.build();
	w.render_scene();

	return 0;
}