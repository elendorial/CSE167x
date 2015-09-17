#include "Constants.h"
#include "Instance.h"
#include <math.h>



Matrix Instance::forward_matrix;


Instance::Instance(void)	
	: 	GeometricObject(),
		object_ptr(NULL),
		inv_matrix()
{
	forward_matrix.set_identity();
}


Instance::Instance(GeometricObject* obj_ptr)     
	:	GeometricObject(),
		object_ptr(obj_ptr),
		inv_matrix()
{
	forward_matrix.set_identity();
}	


Instance::Instance (const Instance& instance)
	: 	GeometricObject(instance),
		inv_matrix(instance.inv_matrix)
{
	if(instance.object_ptr)
		object_ptr = instance.object_ptr->clone(); 
	else  object_ptr = NULL;
}


Instance* Instance::clone(void) const {
	return (new Instance(*this));
}


Instance::~Instance(void) {
	if (object_ptr) {
		delete object_ptr;
		object_ptr = NULL;
	}
}


Instance& Instance::operator= (const Instance& rhs) {
	if (this == &rhs)
		return (*this);

	GeometricObject::operator=(rhs);
		
	if(object_ptr) {
		delete object_ptr;
		object_ptr = NULL;
	}
	
	if (rhs.object_ptr)
		object_ptr = rhs.object_ptr->clone();
	else
		object_ptr = NULL;
	
	inv_matrix = rhs.inv_matrix;
	
	return (*this);
}


void Instance::set_object(GeometricObject* obj_ptr) {
	object_ptr = obj_ptr;
}


Material* Instance::get_material(void) const {
	return (material_ptr);     
}


void Instance::set_material(Material* m_ptr) {
	material_ptr = m_ptr;
}


bool Instance::hit(const Ray& ray, double& t, ShadeRec& sr) const {
	Ray inv_ray(ray);  
	inv_ray.o = inv_matrix * inv_ray.o;   
	inv_ray.d = inv_matrix * inv_ray.d;
				
	if (object_ptr->hit(inv_ray, t, sr)) {
		sr.normal = inv_matrix * sr.normal;
		sr.normal.normalize();				
						
		if (object_ptr->get_material())
			material_ptr = object_ptr->get_material(); 
			

		return (true);
	} 

	return (false);   
}

bool Instance::shadow_hit(const Ray& ray, float& t) const {
	Ray inv_ray(ray);  
	inv_ray.o = inv_matrix * inv_ray.o;   
	inv_ray.d = inv_matrix * inv_ray.d;
				
	if (object_ptr->shadow_hit(inv_ray, t)) {
		return (true);
	} 

	return (false);   

}


void Instance::scale(const Vector3D& s) {

	Matrix	inv_scaling_matrix;			
	
	inv_scaling_matrix.m[0][0] = 1.0 / s.x;
	inv_scaling_matrix.m[1][1] = 1.0 / s.y;
	inv_scaling_matrix.m[2][2] = 1.0 / s.z;

	inv_matrix = inv_scaling_matrix * inv_matrix  ;			

	Matrix	scaling_matrix;				
	
	scaling_matrix.m[0][0] = s.x;
	scaling_matrix.m[1][1] = s.y;
	scaling_matrix.m[2][2] = s.z;
	
	forward_matrix = forward_matrix * scaling_matrix ; 		
}


void Instance::scale(const double a, const double b, const double c) {

	Matrix inv_scaling_matrix;					
	
	inv_scaling_matrix.m[0][0] = 1.0 / a;
	inv_scaling_matrix.m[1][1] = 1.0 / b;
	inv_scaling_matrix.m[2][2] = 1.0 / c;
	
	inv_matrix = inv_scaling_matrix * inv_matrix  ;				

	Matrix scaling_matrix;						
	
	scaling_matrix.m[0][0] = a;
	scaling_matrix.m[1][1] = b;
	scaling_matrix.m[2][2] = c;
	
	forward_matrix = forward_matrix * scaling_matrix ; 		
}


void Instance::translate(const Vector3D& trans) {

	Matrix inv_translation_matrix;		
			
	inv_translation_matrix.m[0][3] = -trans.x;
	inv_translation_matrix.m[1][3] = -trans.y;
	inv_translation_matrix.m[2][3] = -trans.z;
					
	inv_matrix =  inv_translation_matrix * inv_matrix ;
	
	Matrix translation_matrix;			
	
	translation_matrix.m[0][3] = trans.x;
	translation_matrix.m[1][3] = trans.y;
	translation_matrix.m[2][3] = trans.z;
	
	forward_matrix =  forward_matrix * translation_matrix ; 
}


void Instance::translate(const double dx, const double dy, const double dz) {

	Matrix inv_translation_matrix;				
			
	inv_translation_matrix.m[0][3] = -dx;
	inv_translation_matrix.m[1][3] = -dy;
	inv_translation_matrix.m[2][3] = -dz;
					
	inv_matrix =  inv_translation_matrix * inv_matrix ;
	
	Matrix translation_matrix;				
	
	translation_matrix.m[0][3] = dx;
	translation_matrix.m[1][3] = dy;
	translation_matrix.m[2][3] = dz;
	
	forward_matrix =  forward_matrix * translation_matrix ; 
}


void Instance::rotate_x(const double theta) {

	double sin_theta = sin(theta * PI_ON_180);
	double cos_theta = cos(theta * PI_ON_180);
	
	Matrix inv_x_rotation_matrix;					
	
	inv_x_rotation_matrix.m[1][1] = cos_theta;
	inv_x_rotation_matrix.m[1][2] = sin_theta;   	
	inv_x_rotation_matrix.m[2][1] = -sin_theta;  
	inv_x_rotation_matrix.m[2][2] = cos_theta;		
					
	inv_matrix =  inv_x_rotation_matrix * inv_matrix ;	   	
	
	Matrix x_rotation_matrix;					
	
	x_rotation_matrix.m[1][1] = cos_theta;
	x_rotation_matrix.m[1][2] = -sin_theta;
	x_rotation_matrix.m[2][1] = sin_theta;
	x_rotation_matrix.m[2][2] = cos_theta;
				
	forward_matrix =  forward_matrix * x_rotation_matrix ; 
}


void Instance::rotate_y(const double theta) {

	double sin_theta = sin(theta * PI / 180.0);
	double cos_theta = cos(theta * PI / 180.0);

	Matrix inv_y_rotation_matrix;					
	
	inv_y_rotation_matrix.m[0][0] = cos_theta;   
	inv_y_rotation_matrix.m[0][2] = -sin_theta;  
	inv_y_rotation_matrix.m[2][0] = sin_theta;
	inv_y_rotation_matrix.m[2][2] = cos_theta;		
					
	inv_matrix =  inv_y_rotation_matrix * inv_matrix ;	   	
	
	Matrix y_rotation_matrix;						
	
	y_rotation_matrix.m[0][0] = cos_theta;
	y_rotation_matrix.m[0][2] = sin_theta;
	y_rotation_matrix.m[2][0] = -sin_theta;
	y_rotation_matrix.m[2][2] = cos_theta;
				
	forward_matrix =  forward_matrix * y_rotation_matrix ; 
}


void Instance::rotate_z(const double theta) {
	double sin_theta = sin(theta * PI / 180.0);
	double cos_theta = cos(theta * PI / 180.0);

	Matrix inv_z_rotation_matrix;					
	
	inv_z_rotation_matrix.m[0][0] = cos_theta;
	inv_z_rotation_matrix.m[0][1] = sin_theta;   	
	inv_z_rotation_matrix.m[1][0] = -sin_theta;  
	inv_z_rotation_matrix.m[1][1] = cos_theta;	
					
	inv_matrix =  inv_z_rotation_matrix * inv_matrix ;
	
	Matrix z_rotation_matrix;						
	
	z_rotation_matrix.m[0][0] = cos_theta;
	z_rotation_matrix.m[0][1] = -sin_theta;
	z_rotation_matrix.m[1][0] = sin_theta;
	z_rotation_matrix.m[1][1] = cos_theta;
				
	forward_matrix =  forward_matrix * z_rotation_matrix ; 
}


void Instance::shear(const Matrix& s) {
	
	Matrix inverse_shearing_matrix;    
	
	

	double d = 1.0 	- s.m[1][0] * s.m[0][1] - s.m[2][0] * s.m[0][2]  - s.m[2][1] * s.m[1][2]
					+ s.m[1][0] * s.m[2][1] * s.m[0][2] + s.m[2][0] * s.m[0][1] * s.m[2][1];
					
	
	
	inverse_shearing_matrix.m[0][0] = 1.0 - s.m[2][1] * s.m[1][2];
	inverse_shearing_matrix.m[1][1] = 1.0 - s.m[2][0] * s.m[0][2];
	inverse_shearing_matrix.m[2][2] = 1.0 - s.m[1][0] * s.m[0][1];
	inverse_shearing_matrix.m[3][3] = d;
	
	
	
	inverse_shearing_matrix.m[0][1] = -s.m[1][0] + s.m[2][0] * s.m[1][2];
	inverse_shearing_matrix.m[0][2] = -s.m[2][0] + s.m[1][0] * s.m[2][1];
	
	
	
	inverse_shearing_matrix.m[1][0] = -s.m[0][1] + s.m[2][1] * s.m[0][2];
	inverse_shearing_matrix.m[1][2] = -s.m[2][1] + s.m[2][0] * s.m[0][1];
	
	
	
	inverse_shearing_matrix.m[2][0] = -s.m[0][2] + s.m[0][1] * s.m[1][2];
	inverse_shearing_matrix.m[2][1] = -s.m[1][2] + s.m[1][0] * s.m[0][2] ;
	
	
	inverse_shearing_matrix = inverse_shearing_matrix / d;
	
	inv_matrix =  inverse_shearing_matrix * inv_matrix ;	
	
	forward_matrix = forward_matrix * s; 
}

