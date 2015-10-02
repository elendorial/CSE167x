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

#ifndef __LIGHT__
#define __LIGHT__

#include "Vector3D.h"
#include "RGBColor.h"
#include "Ray.h"

class ShadeRec;

class Light {

    public:

        Light(void);

        Light(const Light& ls);

        Light& operator= (const Light& rhs);

        virtual Light* clone(void) const = 0;

        virtual ~Light(void);

        virtual Vector3D get_direction(ShadeRec& sr) = 0;

        virtual bool in_shadow(const Ray& ray, const ShadeRec& sr) const;

        virtual bool casts_shadows() const;

        virtual RGBColor L(ShadeRec& sr);

};

#endif