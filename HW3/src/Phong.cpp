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

#include "Phong.h"

Phong::Phong()
:   Material()
{ambient.r = 0.2; ambient.g = 0.2; ambient.b = 0.2;
diffuse.r = 0; diffuse.g = 0; diffuse.b = 0;
emission.r = 0; emission.g = 0; emission.b = 0;
specular.r = 0; specular.g = 0; specular.b = 0;
shininess = 0;}

Phong::Phong(const Phong& m)
:   Material(m)
{
    ambient = m.ambient;
    diffuse = m.diffuse;
    emission = m.emission;
    shininess = m.shininess;
    specular = m.specular;
}

Material* Phong::clone(void) const {
    return(new Phong(*this));
}

Phong& Phong::operator= (const Phong& rhs) {
    if (this == &rhs)
        return(*this);

    Material::operator=(rhs);

    ambient = rhs.ambient;
    diffuse = rhs.diffuse;
    emission = rhs.emission;
    shininess = rhs.shininess;
    specular = rhs.specular;

    return(*this);
}

Phong::~Phong() {}


RGBColor Phong::shade(ShadeRec& sr) {
    Vector3D wo = -sr.ray.d;
    RGBColor L = ambient + emission;

    int numLights = sr.w.lights.size();

    for(int j = 0; j < numLights; j++) {
        Vector3D wi = sr.w.lights[j]->get_direction(sr);
        Vector3D h(wi + wo);
        h.normalize();
        float ndotwi = sr.normal * wi;
        float ndoth = sr.normal * h;
        bool in_shadow = false;

        if(sr.w.lights[j]->casts_shadows())
        {
            Ray shadowRay(sr.hit_point, wi);
            in_shadow = sr.w.lights[j]->in_shadow(shadowRay, sr);
        }

        if(!in_shadow)
        {
            L += diffuse * sr.w.lights[j]->L(sr) * max(0.0, ndotwi) + specular * sr.w.lights[j]->L(sr) * pow(max(ndoth, 0.0), shininess);
        }


    }

    return(L);

}