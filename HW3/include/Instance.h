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

#ifndef __INSTANCE__
#define __INSTANCE__

#include "GeometricObject.h"
#include "Matrix.h"

class Instance:public GeometricObject {
    public:

        Instance(void);

        Instance(GeometricObject* obj_ptr);

        Instance(const Instance& instance);

        virtual Instance* clone(void) const;

        virtual ~Instance(void);

        Instance& operator= (const Instance& rhs);

        void set_object(GeometricObject* obj_ptr);

        virtual Material* get_material(void) const;

        virtual void set_material(Material* materialPtr);

        virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

        virtual bool shadow_hit(const Ray& ray, float& tmin) const;

        void translate(const Vector3D& trans);

        void translate(const double dx, const double dy, const double dz);

        void scale(const Vector3D& s);

        void scale(const double a, const double b, const double c);

        virtual void rotate_x(const double r);

        virtual void rotate_y(const double r);

        virtual void rotate_z(const double r);

        virtual void rotate(const double axis0, const double axis1, const float axis2, double theta);

        void shear(const Matrix& m);

        Matrix inv_matrix;


    private:

        GeometricObject* object_ptr;

        static Matrix forward_matrix;

};

#endif