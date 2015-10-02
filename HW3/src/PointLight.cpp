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

#include "PointLight.h"

float PointLight::atten0 = 1.0;
float PointLight::atten1 = 0.0;
float PointLight::atten2 = 0.0;

PointLight::PointLight()
:   Light(),
    ls(1.0),
    color(1.0),
    location(0, 1, 0),
    shadows(false)
{}

PointLight::PointLight(const PointLight& pl)
:   Light(pl),
    ls(pl.ls),
    color(pl.color),
    location(pl.location),
    shadows(pl.shadows)
{}

Light* PointLight::clone(void) const {
    return(new PointLight(*this));
}


PointLight& PointLight::operator= (const PointLight& rhs) {
    if(this == &rhs)
        return(*this);

    ls = rhs.ls;
    color = rhs.color;
    location = rhs.location;
    shadows = rhs.shadows;

    return(*this);
}

PointLight::~PointLight() {}

Vector3D PointLight::get_direction(ShadeRec& sr) {
    return((location - sr.hit_point).hat());
}

RGBColor PointLight::L(ShadeRec& sr) {
    float distance = location.distance(sr.hit_point);
    float d_sq = location.d_squared(sr.hit_point);
    return ((ls * color) / (atten0 + atten1 * distance + atten2 * d_sq));
}

bool PointLight::in_shadow(const Ray& ray, const ShadeRec& sr) const {
    float t;
    int num_objects = sr.w.objects.size();
    float d = location.distance(ray.o);

    for(int j = 0; j < num_objects; j++)
        if(sr.w.objects[j]->shadow_hit(ray, t) && t < d)
            return(true);
    return(false);
}

bool PointLight::casts_shadows() const {
    return(shadows);
}

