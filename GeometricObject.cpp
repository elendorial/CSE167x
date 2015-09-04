#include "Constants.h"
#include "Material.h"
#include "GeometricObject.h"


GeometricObject::GeometricObject(void)
: material_ptr(NULL)
{temp_color.r = 1;
temp_color.g = 1;
temp_color.b = 1;}

GeometricObject::GeometricObject(const GeometricObject& object) {
	if(object.material_ptr)
		material_ptr = object.material_ptr -> clone();
	else material_ptr = NULL;

	temp_color.r = object.temp_color.r;
	temp_color.g = object.temp_color.g;
	temp_color.b = object.temp_color.b;

}

GeometricObject& GeometricObject::operator= (const GeometricObject& rhs) {
	if (this == &rhs)
		return (*this);

	if(material_ptr) {
		delete  material_ptr;
		material_ptr = NULL;
	}

	if(rhs.material_ptr)
		material_ptr = rhs.material_ptr -> clone();

	temp_color.r = rhs.temp_color.r;
	temp_color.g = rhs.temp_color.g;
	temp_color.b = rhs.temp_color.b;

	return(*this);
}

GeometricObject::~GeometricObject(void) {
	if(material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}
}

void GeometricObject::set_material(Material* mPtr) {
	material_ptr = mPtr;
}

void GeometricObject::set_color(float r, float g, float b)
{
	temp_color.r = r;
	temp_color.g = g;
	temp_color.b = b;
}