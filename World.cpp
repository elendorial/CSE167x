#include "World.h"
#include "Constants.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "Point2D.h"
#include "Normal.h"
#include "Maths.h"
#include "Matte.h"
#include "Phong.h"
#include "Directional.h"
#include "PointLight.h"
#include <iostream>
#include <cmath>


World::World(void)
:	background_color(black),
	tracer_ptr(NULL),
	camera_ptr(NULL),
	ambient_ptr(new Ambient)
{}

World::~World(void) {
	if(tracer_ptr) {
		delete tracer_ptr;
		tracer_ptr = NULL;
	}
	if(camera_ptr) {
		delete camera_ptr;
		camera_ptr = NULL;
	}

	if(ambient_ptr) {
		delete ambient_ptr;
		ambient_ptr = NULL;
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

ShadeRec World::hit_objects(const Ray& ray) {

	ShadeRec sr(*this);
	double t;
	Normal normal;
	Point3D local_hit_point;
	float tmin = kHugeValue;
	int num_objects = objects.size();

	for(int j = 0; j < num_objects; j++)
		if(objects[j]->hit(ray, t, sr) && (t < tmin)) {
			sr.hit_an_object = true;
			tmin = t;
			sr.material_ptr = objects[j] -> get_material();
			sr.hit_point = ray.o + t * ray.d;
			normal = sr.normal;
			local_hit_point = sr.local_hit_point;
		}
	if(sr.hit_an_object) {
		sr.t = tmin;
		sr.normal = normal;
		sr.local_hit_point = local_hit_point;
	}

	return sr;

}

void World::render_scene(void) const {
	RGBColor pixel_color;
	FreeImage_Initialise();
	FIBITMAP* bitmap = FreeImage_Allocate(vp.hres, vp.vres, 24);
	RGBQUAD color;
	Ray ray;

	ray.o = Point3D(0, 0, 120);

	for(int r = 0; r < vp.vres; r++)
		for(int c = 0; c < vp.hres; c++) {

			ray.d = Vector3D(vp.s * (c - 0.5 * (vp.hres - 1.0)), vp.s * (r - 0.5 * (vp.vres - 1.0)), -100);
			ray.d.normalize();
			pixel_color = tracer_ptr -> trace_ray(ray);
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
	int num_samples = 25;

	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_pixel_size(0.5);
	vp.set_samples(num_samples); 
	
	tracer_ptr = new RayCast(this);
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(1.0);
	set_ambient_light(ambient_ptr);
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 0, 500);
	pinhole_ptr->set_lookat(-15, -10, 0);
	//pinhole_ptr->set_vpd(850.0);
	pinhole_ptr->compute_uvw();     
	set_camera(pinhole_ptr);
	
	PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(100, 50, 150);
	light_ptr2->scale_radiance(3.0); 
	light_ptr2->set_shadows(true); 
	//add_light(light_ptr2);

	Directional* light_ptr3 = new Directional;
	light_ptr3->set_color(1,1,1);
	light_ptr3->set_direction(100,50,150);
	light_ptr3->set_shadows(true);
	add_light(light_ptr3);

	Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ka(0.25);	
	matte_ptr1->set_kd(0.65);
	matte_ptr1->set_cd(1, 1, 0);	  				// yellow	
	Sphere*	sphere_ptr1 = new Sphere(Point3D(10, -5, 0), 27); 
	sphere_ptr1->set_material(matte_ptr1);	   							
	add_object(sphere_ptr1);
	
	Matte* matte_ptr2 = new Matte;
	matte_ptr2->set_ka(0.15);	
	matte_ptr2->set_kd(0.85);
	matte_ptr2->set_cd(0.71, 0.40, 0.16);   		// brown
	Sphere*	sphere_ptr2 = new Sphere(Point3D(-25, 10, -35), 27); 			
	sphere_ptr2->set_material(matte_ptr2);							
	add_object(sphere_ptr2);
	
	Matte* matte_ptr3 = new Matte;
	matte_ptr3->set_ka(0.15);	
	matte_ptr3->set_kd(0.5);
	matte_ptr3->set_cd(0, 0.4, 0.2);				// dark green
	Plane* plane_ptr = new Plane(Point3D(0, 0, -50), Normal(0, 0, 1)); 
	plane_ptr->set_material(matte_ptr3);								
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
	//w.render_scene();
	w.camera_ptr -> render_scene(w);
	

	return 0;
}