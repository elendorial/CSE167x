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
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

This file incorporates work covered by the following copyright and permission notice:

Copyright (C) Kevin Suffern 2000-2007.
This C++ code is for non-commercial purposes only.
This C++ code is licensed under the GNU General Public License Version 2.
See the file COPYING.txt for the full license. */

#ifndef __SPHERE__
#define __SPHERE__

#include "GeometricObject.h"

class Sphere: public GeometricObject{

    public:

        Sphere(void);

        Sphere(Point3D center, double r);

        Sphere(const Sphere& sphere);

        virtual Sphere* clone(void) const;

        virtual ~Sphere(void);

        Sphere& operator= (const Sphere& sphere);

        void set_center(const Point3D& c);

        void set_center(const double x, const double y, const double z);

        void set_radius(const double r);

        virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const;

        virtual bool shadow_hit(const Ray& ray, float& tmin) const;

        virtual void set_color(float r, float g, float b);

        virtual RGBColor get_color() const;

    private:

        Point3D center;
        double radius;

        static const double kEpsilon;
};

inline void Sphere::set_center(const Point3D& c) {
    center = c;
}

inline void Sphere::set_center(const double x, const double y, const double z) {
    center.x = x;
    center.y = y;
    center.z = z;
}

inline void Sphere::set_radius(const double r) {
    radius = r;
}

inline void Sphere::set_color(float r, float g, float b) {

    temp_color.r = r;
    temp_color.g = g;
    temp_color.b = b;
}

inline RGBColor Sphere::get_color() const {
    return (temp_color);
}

#endif