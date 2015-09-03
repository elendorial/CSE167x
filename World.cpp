#include "World.h"
#include "Constants.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "Normal.h"
#include "Ray.h"
#include "Maths.h"


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


RGBColor World::max_to_one(const RGBColor& c) const {
	float max_value = max(c.r, max(c.g, c.b));

	if (max_value > 1.0)
		return (c / max_value);
	else
		return (c);
}

RGBColor World::clamp_to_color(const RGBColor& raw_color) const {
	RGBColor c(raw_color);

	if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
		c.r = 1.0; 
		c.g = 1.0;
		c.b = 1.0;
	}
	return(c);
}


void World::display_pixel(const int row, const int column, const RGBColor& raw_color) const {

	RGBColor mapped_color;

	if(vp.show_out_of_gamut)
		mapped_color = clamp_to_color(raw_color);
	else
		mapped_color = max_to_one(raw_color);

	if(vp.gamma != 1.0)
		mapped_color = mapped_color.powc(vp.inv_gamma);

	int x = column;
	int y = vp.vres - 1 - row;
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
			display_pixel(r, c, pixel_color);

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