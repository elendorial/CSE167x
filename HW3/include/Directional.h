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

#ifndef __DIRECTIONAL__
#define __DIRECTIONAL__

#include "Light.h"
#include "Vector3D.h"
#include "RGBColor.h"
#include "World.h"
#include "ShadeRec.h"

class Directional: public Light {
    public:

        Directional(void);

        Directional(const Directional& dl);

        virtual Light* clone(void) const;

        Directional& operator= (const Directional& rhs);

        virtual ~Directional();

        void scale_radiance(const float b);

        void set_color(const float c);

        void set_color(const RGBColor& c);

        void set_color(const float r, const float g, const float b);

        void set_direction(Vector3D d);

        void set_direction(float dx, float dy, float dz);

        void set_shadows(bool flag);

        virtual Vector3D get_direction(ShadeRec& sr);

        virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;

        virtual bool casts_shadows() const;

        virtual RGBColor L(ShadeRec& sr);

    private:

        float ls;
        RGBColor color;
        Vector3D dir;
        bool shadows;

};

inline void Directional::set_shadows(bool flag) {
    shadows = flag;
}

inline void Directional::scale_radiance(const float b) {
    ls = b;
}

inline void Directional::set_color(const float c) {
    color.r = c; color.g = c; color.b = c;
}

inline void Directional::set_color(const RGBColor& c) {
    color = c;
}

inline void Directional::set_color(const float r, const float g, const float b) {
    color.r = r; color.g = g; color.b = b;
}

inline void Directional::set_direction(Vector3D d) {
    dir = d;
    dir.normalize();
}

inline void Directional::set_direction(float dx, float dy, float dz) {
    dir.x = dx; dir.y = dy; dir.z = dz;
}

#endif