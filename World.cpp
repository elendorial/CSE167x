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
#include "Instance.h"

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

bool World::readvals(std::stringstream &s, const int numvals, float* values) 
{
  for (int i = 0; i < numvals; i++) {
    s >> values[i]; 
    if (s.fail()) {
      std::cout << "Failed reading value " << i << " will skip\n"; 
      return false;
    }
  }
  return true; 
}


void World::build(const char* filename) {
	std::string str, cmd;
	std::ifstream in;
	in.open(filename);
	getline(in, str);

	float diffuse[3];
	float specular[3];
	float emission[3];
	float ambient[3];
	float shininess;

	while(in) {
		if((str.find_first_not_of(" \t\r\n") != std::string::npos) && (str[0] != '#')) {

			std::stringstream s(str);
        	s >> cmd; 
        	bool validInput;
        	float values[10];

        	if(cmd == "camera"){
        		validInput = readvals(s,10,values);
        		if(validInput){
        			Pinhole* camera_ptr = new Pinhole;
        			camera_ptr->set_eye(values[0], values[1], values[2]);
        			camera_ptr->set_lookat(values[3], values[4], values[5]);
        			camera_ptr->set_up_vector(values[6], values[7], values[8]);
        			camera_ptr->set_fovy(values[9]);
        			set_camera(camera_ptr);
        		}
        	}
        	else if(cmd == "directional"){
        		validInput = readvals(s, 6, values);
        		if(validInput) {
        			Directional* light_ptr = new Directional;
        			light_ptr->set_direction(values[0], values[1], values[2]);
        			light_ptr->set_color(values[3], values[4], values[5]);
        			add_light(light_ptr);
        		}
        	}
        	else if(cmd == "point") {
        		validInput = readvals(s, 6, values);
        		if(validInput) {
        			PointLight* light_ptr = new PointLight;
        			light_ptr->set_location(values[0], values[1], values[2]);
        			light_ptr->set_color(values[3], values[4], values[5]);
        			add_light(light_ptr);
        		}
        	}
        	else if(cmd == "size") {
        		validInput = readvals(s, 2, values);
        		if(validInput) {
        			vp.set_hres(values[0]);
        			vp.set_vres(values[1]);
        		}
        	}
        	else if(cmd == "diffuse") {
        		validInput = readvals(s, 3, values);
        		if(validInput) {
        			for(int i = 0; i < 3; i ++)
        				diffuse[i] = values[i];
        		}
        	}
        	else if(cmd == "specular") {
        		validInput = readvals(s, 3, values);
        		if(validInput) {
        			for(int i = 0; i < 3; i ++)
        				specular[i] = values[i];
        		}
        	}
        	else if(cmd == "emission") {
        		validInput = readvals(s, 3, values);
        		if(validInput) {
        			for(int i = 0; i < 3; i ++)
        				emission[i] = values[i];
        		}
        	}
        	else if(cmd == "shininess") {
        		validInput = readvals(s, 1, values);
        		if(validInput) {
        			shininess = values[0];
        		}
        	}
        	else if(cmd == "ambient") {
        		validInput = readvals(s, 3, values);
        		if(validInput) {
        			for(int i = 0; i < 3; i++)
        				ambient[i] = values[i];
        		}
        	}
		}

	}


}

int main(int argc, char* argv[])
{
	World w;
	w.build(argv[1]); 
	if(w.tracer_ptr == NULL) {
		std::cout << "Tracer not Initialized" << std::endl;
		return (-1);
	}
	//w.render_scene();
	w.camera_ptr -> render_scene(w);
	

	return 0;
}