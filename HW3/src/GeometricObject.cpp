/*Copyright (C) 2015  Viktor Daropoulos

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.*/

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

bool GeometricObject::shadow_hit(const Ray& ray, float& tmin) const {
    return(false);
}