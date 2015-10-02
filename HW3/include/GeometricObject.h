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

#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

class Material;

#include "Point3D.h"
#include "Ray.h"
#include "ShadeRec.h"


class GeometricObject
{
    public:

        GeometricObject(void);

        GeometricObject(const GeometricObject& object);

        virtual GeometricObject* clone(void) const = 0;

        virtual ~GeometricObject(void);

        virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const = 0;

        virtual bool shadow_hit(const Ray& ray, float& tmin) const;

        Material* get_material(void) const;

        virtual void set_material(Material* mPtr);

        virtual void set_color(float r, float g, float b);

        virtual RGBColor get_color() const;

    protected:

        mutable Material* material_ptr;

        GeometricObject& operator= (const GeometricObject& rhs);

        RGBColor temp_color;

};


inline Material* GeometricObject::get_material(void) const {
    return (material_ptr);
}

inline RGBColor GeometricObject::get_color() const {
    return (temp_color);
}

#endif