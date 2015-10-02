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

#ifndef __CAMERA__
#define __CAMERA__

#include "Point3D.h"
#include "Vector3D.h"

class World;

class Camera {

    public:

        Camera();

        Camera(const Camera& camera);

        virtual Camera* clone(void) const = 0;

        virtual ~Camera();

        virtual void render_scene(World& w) = 0;

        void set_eye(const Point3D& p);

        void set_eye(const float x, const float y, const float z);

        void set_lookat(const Point3D& p);

        void set_lookat(const float x, const float y, const float z);

        void set_up_vector(const Vector3D& u);

        void set_up_vector(const float x, const float y, const float z);

        void set_roll(const float ra);

        void set_exposure_time(const float exposure);

        void compute_uvw(void);

    protected:

        Point3D eye;
        Point3D lookat;
        float ra;
        Vector3D u, v, w;
        Vector3D up;
        float exposure_time;


        Camera& operator= (const Camera& camera);

};

inline void Camera::set_eye(const Point3D& p) {
    eye = p;
}

inline void Camera::set_eye(const float x, const float y, const float z) {
    eye.x = x; eye.y = y; eye.z = z;
}

inline void Camera::set_lookat(const Point3D& p) {
    lookat = p;
}

inline void Camera::set_lookat(const float x, const float y, const float z) {
    lookat.x = x; lookat.y = y; lookat.z = z;
}

inline void Camera::set_up_vector(const Vector3D& u) {
    up = u;
}

inline void Camera::set_up_vector(const float x, const float y, const float z) {
    up.x = x; up.y = y; up.z = z;
}

inline void Camera::set_roll(const float r) {
    ra = r;
}

inline void Camera::set_exposure_time(const float exposure){
    exposure_time = exposure;
}

#endif