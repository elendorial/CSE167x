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

#ifndef __PHONG__
#define __PHONG__

#include "Material.h"

class Phong: public Material {
    public:

        Phong(void);

        Phong(const Phong& ph);

        virtual Material* clone(void) const;

        Phong& operator= (const Phong& rhs);

        ~Phong();

        virtual RGBColor shade(ShadeRec& sr);

        void set_ambient(const float r, const float g, const float b);

        void set_diffuse(const float r, const float g, const float b);

        void set_emission(const float r, const float g, const float b);

        void set_specular(const float r, const float g, const float b);

        void set_shininess(const float s);

        RGBColor specular;

    private:

        RGBColor ambient;
        RGBColor diffuse;
        RGBColor emission;

        float shininess;
};

inline void Phong::set_specular(const float r, const float g, const float b){
    specular.r = r;
    specular.g = g;
    specular.b = b;
}

inline void Phong::set_ambient(const float r, const float g, const float b) {
    ambient.r = r;
    ambient.g = g;
    ambient.b = b;
}

inline void Phong::set_diffuse(const float r, const float g, const float b) {
    diffuse.r = r;
    diffuse.g = g;
    diffuse.b = b;
}

inline void Phong::set_emission(const float r, const float g, const float b) {
    emission.r = r;
    emission.g = g;
    emission.b = b;
}

inline void Phong::set_shininess(const float s){
    shininess = s;
}


#endif