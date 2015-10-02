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
#include "Normal.h"

Normal::Normal(void)
: x(0.0), y(0.0), z(0.0)
{}

Normal::Normal(double a)
: x(a), y(a), z(a)
{}

Normal::Normal(double _x, double _y, double _z)
: x(_x), y(_y), z(_z)
{}

Normal::Normal(const Normal& n)
: x(n.x), y(n.y), z(n.z)
{}

Normal::Normal(const Vector3D& v)
: x(v.x), y(v.y), z(v.z)
{}

Normal::~Normal(void)
{}

Normal& Normal::operator= (const Normal& rhs) {
    if (this == &rhs)
        return (*this);

    x = rhs.x; y = rhs.y; z = rhs.z;

    return(*this);
}

Normal& Normal::operator= (const Vector3D& rhs) {
    x = rhs.x; y = rhs.y; z = rhs.z;
    return(*this);
}

Normal& Normal::operator= (const Point3D& rhs) {
    x = rhs.x; y = rhs.y; z = rhs.z;
    return (*this);
}

void Normal::normalize(void) {
    double length = sqrt(x * x + y * y + z * z);
    x /= length; y /= length; z /= length;
}

// non-member function definition

// ---------------------------------------------------------- operator*
// multiplication by a matrix on the left

// a normal is transformed by multiplying it on the left by the transpose of the upper left 3 x 3
// partition of the inverse transformation matrix


Normal operator* (const Matrix& mat, const Normal& n) {
    return (Normal( mat.m[0][0] * n.x + mat.m[1][0] * n.y + mat.m[2][0] * n.z,
                    mat.m[0][1] * n.x + mat.m[1][1] * n.y + mat.m[2][1] * n.z,
                    mat.m[0][2] * n.x + mat.m[1][2] * n.y + mat.m[2][2] * n.z));

}