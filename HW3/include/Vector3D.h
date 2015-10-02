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

#ifndef __VECTOR_3D__
#define __VECTOR_3D__

#include "Matrix.h"

class Normal;
class Point3D;


class Vector3D {
public:

    double x, y, z;

public:

    Vector3D(void);
    Vector3D(double a);
    Vector3D(double _x, double _y, double _z);
    Vector3D(const Vector3D& v);
    Vector3D(const Normal& n);
    Vector3D(const Point3D& p);

    ~Vector3D(void);

    Vector3D& operator= (const Vector3D& rhs);

    Vector3D& operator= (const Normal& rhs);

    Vector3D& operator= (const Point3D& rhs);

    Vector3D operator- (void) const;

    double length(void);

    double len_squared(void);

    Vector3D operator* (const double a) const;

    Vector3D operator/ (const double a) const;

    Vector3D operator+ (const Vector3D& v) const;

    Vector3D& operator+= (const Vector3D& v);

    Vector3D operator- (const Vector3D& v) const;

    double operator* (const Vector3D& b) const;

    Vector3D operator^ (const Vector3D& v) const;

    void normalize(void);

    Vector3D& hat(void);
};

inline Vector3D Vector3D::operator- (void) const {
    return (Vector3D(-x, -y, -z));
}

inline double Vector3D::len_squared(void) {
    return (x * x + y * y + z * z);
}

inline Vector3D Vector3D::operator* (const double a) const {
    return (Vector3D(x *a, y * a, z * a));
}

inline Vector3D Vector3D::operator/ (const double a) const {
    return (Vector3D(x / a, y / a, z / a));
}

inline Vector3D Vector3D::operator+ (const Vector3D& v) const {
    return (Vector3D(x + v.x, y + v.y, z + v.z));
}

inline Vector3D Vector3D::operator- (const Vector3D& v) const {
    return (Vector3D(x - v.x, y - v.y, z - v.z));
}

inline double Vector3D::operator* (const Vector3D& v) const {
    return (x * v.x + y * v.y + z * v.z);
}

inline Vector3D Vector3D::operator^ (const Vector3D& v) const {
    return (Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x));
}

inline Vector3D& Vector3D::operator+= (const Vector3D& v) {
    x += v.x; y+= v.y; z += v.z;
    return (*this);
}

// inlined non-member function

// ----------------------------------------------------------------------- operator*
// multiplication by a double on the left

Vector3D operator* (const double a, const Vector3D& v);

inline Vector3D operator* (const double a, const Vector3D& v) {
    return (Vector3D(a * v.x, a * v.y, a * v.z));
}

// non-inlined non-member function

// ----------------------------------------------------------------------- operator*
// multiplication by a matrix on the left

Vector3D operator* (const Matrix& mat, const Vector3D& v);

#endif

