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

#include <math.h>
#include "Point3D.h"

Point3D::Point3D()
: x(0), y(0), z(0)
{}

Point3D::Point3D(const double a)
: x(a), y(a), z(a)
{}

Point3D::Point3D(const double a, const double b, const double c)
: x(a), y(b), z(c)
{}

Point3D::Point3D(const Point3D& p)
: x(p.x), y(p.y), z(p.z)
{}

Point3D::~Point3D()
{}

Point3D& Point3D::operator= (const Point3D& rhs) {
    if(this == &rhs)
        return (*this);

    x = rhs.x; y = rhs.y; z = rhs.z;

    return(*this);
}

double Point3D::distance(const Point3D& p) const {
    return (sqrt(       (x - p.x) * (x - p.x)
                    +   (y - p.y) * (y - p.y)
                    +   (z - p.z) * (z - p.z) ));

}

Point3D operator* (const Matrix& mat, const Point3D& p) {
    return (Point3D(mat.m[0][0] * p.x + mat.m[0][1] * p.y + mat.m[0][2] * p.z + mat.m[0][3],
                    mat.m[1][0] * p.x + mat.m[1][1] * p.y + mat.m[1][2] * p.z + mat.m[1][3],
                    mat.m[2][0] * p.x + mat.m[2][1] * p.y + mat.m[2][2] * p.z + mat.m[2][3]));

}