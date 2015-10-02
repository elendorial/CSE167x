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

#ifndef __NORMAL__
#define __NORMAL__

#include "Matrix.h"
#include "Vector3D.h"
#include "Point3D.h"

class Normal
{

    public:

        double x, y, z;

    public:

        Normal(void);
        Normal(double a);
        Normal(double _x, double _y, double _z);
        Normal(const Normal& n);
        Normal(const Vector3D& v);

        ~Normal(void);

        Normal& operator= (const Normal& rhs);

        Normal& operator= (const Vector3D& rhs);

        Normal& operator= (const Point3D& rhs);

        Normal operator- (void) const;

        Normal operator+ (const Normal& n) const;

        Normal& operator+= (const Normal& n);

        double operator* (const Vector3D& v) const;

        Normal operator* (const double a) const;

        void normalize(void);
};

inline Normal Normal::operator- (void) const {
    return (Normal(-x, -y, -z));
}

inline Normal Normal::operator+ (const Normal& n) const {
    return (Normal(x + n.x, y + n.y, z + n.z));
}

inline Normal& Normal::operator+= (const Normal& n) {
    x += n.x; y += n.y; z += n.z;
    return (*this);
}

inline double Normal::operator* (const Vector3D& v) const {
    return(x * v.x + y * v.y + z * v.z);
}

inline Normal Normal::operator* (const double a) const {
    return (Normal(x * a, y * a, z * a));
}

Normal operator* (const double a, const Normal& n);

inline Normal operator*(const double f, const Normal& n) {
    return (Normal(f * n.x, f * n.y, f * n.z));
}

Vector3D operator+ (const Vector3D& v, const Normal& n);

inline Vector3D operator+ (const Vector3D& v, const Normal& n) {
    return (Vector3D(v.x + n.x, v.y + n.y, v.z + n.z));
}

Vector3D operator- (const Vector3D&, const Normal& n);

inline Vector3D operator- (const Vector3D& v, const Normal& n) {
    return (Vector3D(v.x - n.x, v.y - n.y, v.z - n.z));
}

double operator* (const Vector3D& v, const Normal& n);

inline double operator* (const Vector3D& v, const Normal& n) {
    return (v.x * n.x + v.y * n.y + v.z * n.z);
}

Normal operator* (const Matrix& mat, const Normal& n);

#endif