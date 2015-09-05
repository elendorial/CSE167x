#include "World.h"
#include "Constants.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "Point2D.h"
#include "Normal.h"
#include "Maths.h"
#include <iostream>
#include <cmath>


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
		c.g = 0.0;
		c.b = 0.0;
	}
	return(c);
}


void World::display_pixel(const int row, const int column, RGBColor& raw_color) const {

	RGBColor mapped_color;

	if(vp.show_out_of_gamut)
		mapped_color = clamp_to_color(raw_color);
	else
		mapped_color = max_to_one(raw_color);

	if(vp.gamma != 1.0)
		mapped_color = mapped_color.powc(vp.inv_gamma);

	raw_color.r = mapped_color.r;
	raw_color.g = mapped_color.g;
	raw_color.b = mapped_color.b;
}

ShadeRec World::hit_bare_bones_objects(const Ray& ray)  {
	ShadeRec sr(*this);
	double t;
	double tmin = kHugeValue;
	int num_objects = objects.size();

	for(int j = 0; j < num_objects; j++)
		if(objects[j] -> hit(ray, t, sr) && (t < tmin)) {
			sr.hit_an_object = true;
			tmin = t;
			sr.color = objects[j] -> get_color();
		}
	return (sr);
}

void World::render_scene(void) const {
	RGBColor pixel_color;
	FreeImage_Initialise();
	FIBITMAP* bitmap = FreeImage_Allocate(vp.hres, vp.vres, 24);
	RGBQUAD color;
	Ray ray;
	double zw = 100.0;
	double x, y;
	int n = (int)sqrt((float)vp.num_samples);
	Point2D pp;

	ray.d = Vector3D(0, 0, -1);

	for(int r = 0; r < vp.vres; r++)
		for(int c = 0; c < vp.hres; c++) {
			//x = vp.s * (c - 0.5 * (vp.hres - 1.0));
			//y = vp.s * (r - 0.5 * (vp.vres - 1.0));

			pixel_color = black;

			// for(int p = 0; p <  n; p++)
			// 	for(int q = 0; q < n; q++) {
			// 		pp.x = vp.s * (c - 0.5 * vp.hres + (q + 0.5) / n);
			// 		pp.y = y = vp.s * (r - 0.5 * vp.vres + (p + 0.5) / n);
			// 		ray.o = Point3D(pp.x, pp.y, zw);
			// 		pixel_color += tracer_ptr -> trace_ray(ray);
			// 	}
			// for(int p = 0; p < vp.num_samples; p++) {
			// 	pp.x = vp.s * (c - 0.5 * vp.hres + rand_float());
			// 	pp.y = vp.s * (r - 0.5 * vp.vres + rand_float());
			// 	ray.o = Point3D(pp.x, pp.y, zw);
			// 	pixel_color += tracer_ptr -> trace_ray(ray);
			// }
			for(int p = 0; p <  n; p++)
				for(int q = 0; q < n; q++) {
					pp.x = vp.s * (c - 0.5 * vp.hres + (q + rand_float()) / n);
					pp.y = y = vp.s * (r - 0.5 * vp.vres + (p + rand_float()) / n);
					ray.o = Point3D(pp.x, pp.y, zw);
					pixel_color += tracer_ptr -> trace_ray(ray);
				}
			pixel_color /= vp.num_samples;
			display_pixel(r, c, pixel_color);
			color.rgbRed = (int)(pixel_color.r*255);
			color.rgbGreen = (int)(pixel_color.g*255);
			color.rgbBlue = (int)(pixel_color.b*255);
			FreeImage_SetPixelColor(bitmap, c, r, &color); 

		}
	if (FreeImage_Save(FIF_PNG, bitmap, "test.png", 0))
		std::cout << "Image Successfully Saved!" << std::endl;

    FreeImage_DeInitialise();
}

void World::build(void) {
	vp.set_hres(300);
	vp.set_vres(300);
	vp.set_samples(36);
	background_color = black;
	tracer_ptr = new MultipleObjects(this);

	Sphere* sphere_ptr1 = new Sphere();
	sphere_ptr1 -> set_center(0, -25, 0);
	sphere_ptr1 -> set_radius(80);
	sphere_ptr1 -> set_color(1, 0, 0);
	add_object(sphere_ptr1);

	Sphere* sphere_ptr2 = new Sphere(Point3D(0, 30, 0), 60);
	sphere_ptr2 -> set_color(1, 1, 0);
	add_object(sphere_ptr2);

	Plane* plane_ptr = new Plane(Point3D(0, 0, 0), Normal(0, 1, 1));
	plane_ptr -> set_color(0.0, 0.3, 0.0);
	add_object(plane_ptr);
}

int main(void)
{
	World w;
	w.build(); 
	if(w.tracer_ptr == NULL) {
		std::cout << "Tracer not Initialized" << std::endl;
		return (-1);
	}
	w.render_scene();

	return 0;
}