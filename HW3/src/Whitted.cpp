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

#include "Whitted.h"
#include "World.h"
#include "ShadeRec.h"
#include "Material.h"

Whitted::Whitted(void)
:   Tracer()
{}

Whitted::Whitted(World* _worldPtr)
:   Tracer(_worldPtr)
{}

Whitted::~Whitted(void) {}

RGBColor Whitted::trace_ray(const Ray ray, const int depth) const {
    if(depth > world_ptr->vp.max_depth)
        return(black);
    else
    {
        ShadeRec sr(world_ptr->hit_objects(ray));

        if(sr.hit_an_object) {
            sr.depth = depth;
            sr.ray = ray;
            return(sr.material_ptr->shade(sr));
        }
        else
            return(world_ptr->background_color);
    }
}