#include "World.h"
#include "Constants.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "Point2D.h"
#include "Normal.h"
#include "Maths.h"
#include "Phong.h"
#include "Reflective.h"
#include "Directional.h"
#include "PointLight.h"
#include "Instance.h"
#include <cmath>
#include <stack>


World::World(void)
:	background_color(black),
tracer_ptr(NULL),
camera_ptr(NULL)
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

	float diffuse[] = {0.0, 0.0, 0.0};
	float specular[] = {0.0, 0.0, 0.0};
	float emission[] = {0.0, 0.0, 0.0};
	float ambient[] = {0.2, 0.2, 0.2};
	float shininess = 0;

	std::stack <Matrix> transfstack; 
	Instance* dummy_instance = new Instance();
	transfstack.push(dummy_instance->inv_matrix);

	getline(in, str);
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
					camera_ptr->compute_uvw();
					camera_ptr->set_fovy(values[9]);
					camera_ptr->set_view_distance((vp.vres / 2) / tan((values[9] / 2) * PI_ON_180));
					set_camera(camera_ptr);
				}
			}
			else if(cmd == "maxdepth") {
				validInput = readvals(s, 1, values);
				if(validInput) {
					vp.set_max_depth(values[0]);
				}
			}
			else if(cmd == "directional"){
				validInput = readvals(s, 6, values);
				if(validInput) {
					Directional* light_ptr = new Directional;
					light_ptr->set_direction(values[0], values[1], values[2]);
					light_ptr->set_color(values[3], values[4], values[5]);
					light_ptr->set_shadows(true);
					add_light(light_ptr);
				}
			}
			else if(cmd == "point") {
				validInput = readvals(s, 6, values);
				if(validInput) {
					PointLight* light_ptr = new PointLight;
					light_ptr->set_location(values[0], values[1], values[2]);
					light_ptr->set_color(values[3], values[4], values[5]);
					light_ptr->set_shadows(true);
					add_light(light_ptr);
				}
			}
			else if(cmd == "attenuation") {
				validInput = readvals(s, 3, values);
				if(validInput) {
					PointLight::atten0 = values[0];
					PointLight::atten1 = values[1];
					PointLight::atten2 = values[2];
				}
			}
			else if(cmd == "size") {
				validInput = readvals(s, 2, values);
				if(validInput) {
					vp.set_hres(values[0]);
					vp.set_vres(values[1]);
					vp.set_samples(1);
					vp.set_pixel_size(1.0);
					vp.set_max_depth(0);
					tracer_ptr = new Whitted(this);
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
			else if(cmd == "sphere"){
				validInput = readvals(s, 4, values);
				if(validInput) {
					Instance* obj = new Instance(new Sphere(Point3D(values[0], values[1], values[2]), values[3]));
					Reflective* phong_ptr = new Reflective;
					phong_ptr->set_ambient(ambient[0], ambient[1], ambient[2]);
					phong_ptr->set_emission(emission[0], emission[1], emission[2]);
					phong_ptr->set_diffuse(diffuse[0], diffuse[1], diffuse[2]);
					phong_ptr->set_specular(specular[0], specular[1], specular[2]);
					phong_ptr->set_shininess(shininess);
					obj->set_material(phong_ptr);
					obj->inv_matrix = dummy_instance->inv_matrix;
					add_object(obj);
				}
			}
			else if(cmd == "translate"){
				validInput = readvals(s, 3, values);
				if(validInput) {
					
					dummy_instance->translate(values[0], values[1], values[2]);

				}
			}
			else if(cmd == "scale"){
				validInput = readvals(s, 3, values);
				if(validInput){
					
					dummy_instance->scale(values[0], values[1], values[2]);
				}
			}
			else if(cmd == "rotate"){
				validInput = readvals(s, 4, values);
				if(validInput) {
					
					dummy_instance->rotate(values[0], values[1], values[2], values[3]);

				}
			}
			else if(cmd == "vertex"){
				validInput = readvals(s,3, values);
				if(validInput){
					Point3D ver(values[0], values[1], values[2]);
					add_vertex(ver);
				}
			}
			else if(cmd == "tri"){
				validInput = readvals(s, 3, values);
				if(validInput){
					Instance* obj = new Instance(new Triangle(vertices[values[0]], vertices[values[1]], vertices[values[2]]));
					Reflective* phong_ptr = new Reflective;
					phong_ptr->set_ambient(ambient[0], ambient[1], ambient[2]);
					phong_ptr->set_emission(emission[0], emission[1], emission[2]);
					phong_ptr->set_diffuse(diffuse[0], diffuse[1], diffuse[2]);
					phong_ptr->set_specular(specular[0], specular[1], specular[2]);
					phong_ptr->set_shininess(shininess);
					obj->set_material(phong_ptr);
					obj->inv_matrix = dummy_instance->inv_matrix;
					add_object(obj);
				}
			}
			else if(cmd == "maxverts"){
				validInput = readvals(s, 0, values);
			}
			else if(cmd == "popTransform") {
				
				dummy_instance->inv_matrix = transfstack.top();
				transfstack.pop();         
			}
			else if(cmd =="pushTransform")
			{
				transfstack.push(dummy_instance->inv_matrix);

			}
			else {
				std::cerr << "Unknown Command: " << cmd << " Skipping \n"; 
			}
		}
		getline (in, str); 
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