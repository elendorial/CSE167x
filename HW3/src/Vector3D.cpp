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

#include "Vector3D.h"
#include "Normal.h"
#include "Point3D.h"

Vector3D::Vector3D(void)
: x(0.0), y(0.0), z(0.0)
{}

Vector3D::Vector3D(double a)
: x(a), y(a), z(a)
{}

Vector3D::Vector3D(double _x, double _y, double _z)
: x(_x), y(_y), z(_z)
{}

Vector3D::Vector3D(const Vector3D& vector)
: x(vector.x), y(vector.y), z(vector.z)
{}

Vector3D::Vector3D(const Normal& n)
: x(n.x), y(n.y), z(n.z)
{}

Vector3D::Vector3D(const Point3D& p)
: x(p.x), y(p.y), z(p.z)
{}

Vector3D::~Vector3D(void)
{}

Vector3D& Vector3D::operator= (const Vector3D& rhs){
    if(this == &rhs)
        return (*this);

    x = rhs.x; y = rhs.y; z = rhs.z;

    return (*this);

}

Vector3D& Vector3D::operator= (const Normal& rhs){
    x = rhs.x; y = rhs.y; z = rhs.z;
    return (*this);
}

Vector3D& Vector3D::operator= (const Point3D& rhs){
    x = rhs.x; y = rhs.y; z = rhs.z;
    return (*this);
}

double Vector3D::length(void){
    return(sqrt(x * x + y * y + z * z));
}

void Vector3D::normalize(void) {
    double length = sqrt(x * x + y * y + z * z);
    x /= length; y /= length; z /= length;
}

Vector3D& Vector3D::hat(void){
    double length = sqrt(x * x + y * y + z * z);
    x /= length; y /= length; z /= length;
    return (*this);
}

Vector3D operator* (const Matrix& mat, const Vector3D& v) {
    return (Point3D(mat.m[0][0] * v.x + mat.m[0][1] * v.y + mat.m[0][2] * v.z,
                    mat.m[1][0] * v.x + mat.m[1][1] * v.y + mat.m[1][2] * v.z,
                    mat.m[2][0] * v.x + mat.m[2][1] * v.y + mat.m[2][2] * v.z));
}

