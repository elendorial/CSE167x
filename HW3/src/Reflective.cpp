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

#include "Reflective.h"

Reflective::Reflective(void)
:   Phong()
{}

Reflective::Reflective(const Reflective& rm)
:   Phong(rm)
{}

Reflective& Reflective::operator= (const Reflective& rhs){
    if(this == &rhs)
        return(*this);

    Phong::operator=(rhs);

    return(*this);
}

Reflective* Reflective::clone(void) const {
    return(new Reflective(*this));
}

Reflective::~Reflective()
{}

RGBColor Reflective::shade(ShadeRec& sr) {
    RGBColor L(Phong::shade(sr));

    Vector3D wo = -sr.ray.d;
    float ndotwo = sr.normal * wo;
    Vector3D wi = -wo + 2.0 * sr.normal * ndotwo;
    Ray reflected_ray(sr.hit_point, wi);

    L += specular * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1);

    return(L);

}