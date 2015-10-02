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

#include "Light.h"
#include "Constants.h"
#include "ShadeRec.h"

Light::Light(void) {}

Light::Light(const Light& ls) {}

Light& Light::operator= (const Light& rhs) {
    if(this == &rhs)
        return(*this);

    return(*this);
}

Light::~Light(void) {}

RGBColor Light::L(ShadeRec& s) {
    return (black);
}

bool Light::in_shadow(const Ray& ray, const ShadeRec& sr) const {
    return(false);
}

bool Light::casts_shadows() const {
    return(false);
}