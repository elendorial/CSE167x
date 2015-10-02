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

#ifndef __TRIANGLE__
#define __TRIANGLE__

#include "GeometricObject.h"

class Triangle: public GeometricObject {
    public:

        Triangle(void);

        Triangle(const Point3D& a, const Point3D& b, const Point3D& c);

        virtual Triangle* clone(void) const;

        Triangle(const Triangle& triangle);

        ~Triangle();

        Triangle& operator= (const Triangle& rhs);

        void compute_normal(void);

        virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

        virtual bool shadow_hit(const Ray& ray, float& tmin) const;

    private:

        Point3D v0, v1, v2;
        Normal normal;
};

#endif