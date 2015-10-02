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

#include "Ray.h"

Ray::Ray(void)
: o(0.0), d(0.0,0.0,1.0)
{}

Ray::Ray(const Point3D& origin, const Vector3D& dir)
: o(origin), d(dir)
{}

Ray::Ray(const Ray& ray)
: o(ray.o), d(ray.d)
{}

Ray& Ray::operator= (const Ray& rhs)
{
    if(this == &rhs)
        return (*this);

    o = rhs.o;
    d = rhs.d;

    return (*this);
}

Ray::~Ray(void) {}