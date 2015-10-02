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

#include "Directional.h"

Directional::Directional(void)
:   Light(),
    ls(1.0),
    color(1.0),
    dir(0, 1, 0),
    shadows(false)
{}

Directional::Directional(const Directional& dl)
:   Light(dl),
    ls(dl.ls),
    color(dl.color),
    dir(dl.dir),
    shadows(dl.shadows)
{}

Light* Directional::clone(void) const {
    return(new Directional(*this));
}

Directional& Directional::operator= (const Directional& rhs) {
    if(this == &rhs)
        return(*this);

    Light::operator=(rhs);

    ls = rhs.ls;
    color = rhs.color;
    dir = rhs.dir;
    shadows = rhs.shadows;

    return(*this);
}

Directional::~Directional() {}

Vector3D Directional::get_direction(ShadeRec& sr) {
    return (dir);
}

RGBColor Directional::L(ShadeRec& s) {
    return(ls * color);
}

bool Directional::in_shadow(const Ray& ray, const ShadeRec& sr) const {
    float t;
    int num_objects = sr.w.objects.size();

    for(int j = 0; j < num_objects; j++)
        if(sr.w.objects[j]->shadow_hit(ray,t))
            return(true);
    return(false);
}

bool Directional::casts_shadows() const{
    return(shadows);
}