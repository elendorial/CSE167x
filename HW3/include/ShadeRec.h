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

#ifndef __SHADE_REC__
#define __SHADE_REC__

#include <vector>

class Material;
class World;


#include "Point3D.h"
#include "Normal.h"
#include "Ray.h"
#include "RGBColor.h"


class ShadeRec
{
    public:

        bool hit_an_object;
        Material* material_ptr;
        Point3D hit_point;
        Point3D local_hit_point;
        Normal normal;
        Ray ray;
        int depth;
        float t;
        Vector3D dir;
        World& w;
        RGBColor color;

        ShadeRec(World& wr);

        ShadeRec(const ShadeRec& sr);

};

#endif