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

#ifndef __POINT3D__
#define __POINT3D__

#include "Matrix.h"
#include "Vector3D.h"

class Point3D
{
    public:

        double x, y, z;

        Point3D();
        Point3D(const double a);
        Point3D(const double a, const double b, const double c);
        Point3D(const Point3D& p);
        ~Point3D();

        Point3D& operator= (const Point3D& p);

        Point3D operator- (void) const;

        Vector3D operator- (const Point3D& p) const;

        Point3D operator+ (const Vector3D& v) const;

        Point3D operator- (const Vector3D& v) const;

        Point3D operator* (const double a) const;

        double d_squared(const Point3D& p) const;

        double distance(const Point3D& p) const;
};

inline Point3D Point3D::operator- (void) const {
    return (Point3D(-x, -y, -z));
}

inline Vector3D Point3D::operator- (const Point3D& p) const {
    return (Vector3D(x - p.x, y - p.y, z - p.z));
}

inline Point3D Point3D::operator+ (const Vector3D& v) const {
    return (Point3D(x + v.x, y + v.y, z + v.z));
}

inline Point3D Point3D::operator- (const Vector3D& v) const {
    return (Point3D(x - v.x, y - v.y, z - v.z));
}

inline Point3D Point3D::operator* (const double a) const {
    return (Point3D(x * a, y * a, z * a));
}

inline double Point3D::d_squared(const Point3D& p) const {
    return (    (x - p.x) * (x - p.x)
            +   (y - p.y) * (y - p.y)
            +   (z - p.z) * (z - p.z) );

}

Point3D operator* (double a, const Point3D& p);

inline Point3D operator* (double a, const Point3D& p) {
    return(Point3D(a * p.x, a * p.y, a * p.z));
}

Point3D operator* (const Matrix& mat, const Point3D& p);

#endif