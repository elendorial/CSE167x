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

#include "Tracer.h"

Tracer::Tracer(void)
:   world_ptr(NULL)
{}

Tracer::Tracer(World* _worldPtr)
:   world_ptr(_worldPtr)
{}

Tracer::~Tracer(void) {
    if(world_ptr)
        world_ptr = NULL;
}

RGBColor Tracer::trace_ray(const Ray& ray) const {
    return(black);
}

RGBColor Tracer::trace_ray(const Ray ray, const int depth) const {
    return(black);
}