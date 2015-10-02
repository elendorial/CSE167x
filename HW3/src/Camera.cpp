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

#include "Camera.h"

Camera::Camera(void)
:   eye(0, 0, 500),
    lookat(0),
    ra(0),
    up(0, 1, 0),
    u(1, 0, 0),
    v(0, 1, 0),
    w(0, 0, 1),
    exposure_time(1.0)
{}

Camera::Camera(const Camera& c)
:   eye(c.eye),
    lookat(c.lookat),
    ra(c.ra),
    up(c.up),
    u(c.u),
    v(c.v),
    w(c.w),
    exposure_time(c.exposure_time)
{}

Camera& Camera::operator= (const Camera& rhs) {
    if(this == &rhs)
        return(*this);

    eye = rhs.eye;
    lookat = rhs.lookat;
    ra = rhs.ra;
    up = rhs.up;
    u = rhs.u;
    v = rhs.v;
    w = rhs.w;
    exposure_time = rhs.exposure_time;

    return(*this);
}

Camera::~Camera(void) {}

void Camera::compute_uvw(void) {

    w = eye - lookat;
    w.normalize();
    u = up ^ w;
    u.normalize();
    v = w ^ u;

    if(eye.x == lookat.x && eye.z == lookat.z && eye.y > lookat.y) {
        u = Vector3D(0, 0, 1);
        v = Vector3D(1, 0, 0);
        w = Vector3D(0, 1, 0);
    }

    if(eye.x == lookat.x && eye.z == lookat.z && eye.y < lookat.y)
    {
        u = Vector3D(1, 0, 0);
        v = Vector3D(0, 0, 1);
        w = Vector3D(0, -1, 0);
    }
}