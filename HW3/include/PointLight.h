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

#ifndef __POINT_LIGHT__
#define __POINT_LIGHT__

#include "Light.h"
#include "Vector3D.h"
#include "RGBColor.h"
#include "World.h"
#include "ShadeRec.h"

class PointLight: public Light {
    public:

        PointLight();

        PointLight(const PointLight& pl);

        virtual Light* clone(void) const;

        PointLight& operator= (const PointLight& rhs);

        virtual ~PointLight();

        void scale_radiance(const float b);

        void set_color(const float c);

        void set_color(const RGBColor& c);

        void set_color(const float r, const float g, const float b);

        void set_location(const float _x, const float _y, const float _z);

        void set_attenuation(const float c0, const float c1, const float c2);

        void set_shadows(bool flag);

        virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;

        virtual bool casts_shadows() const;

        virtual Vector3D get_direction(ShadeRec& sr);

        virtual RGBColor L(ShadeRec& sr);

        static float atten0;

        static float atten1;

        static float atten2;

    private:

        float ls;
        RGBColor color;
        Point3D location;
        bool shadows;


};

inline void PointLight::set_attenuation(const float c0, const float c1, const float c2) {

    atten0 = c0;
    atten1 = c1;
    atten2 = c2;

}

inline void PointLight::set_shadows(bool flag) {
    shadows = flag;
}

inline void PointLight::set_location(const float _x, const float _y, const float _z) {
    location.x = _x;
    location.y = _y;
    location.z = _z;
}

inline void PointLight::scale_radiance(const float b) {
    ls = b;
}

inline void PointLight::set_color(const float c) {
    color.r = c; color.g = c; color.b = c;
}

inline void PointLight::set_color(const RGBColor& c) {
    color = c;
}

inline void PointLight::set_color(const float r, const float g, const float b) {
    color.r = r; color.g = g; color.b = b;
}

#endif
